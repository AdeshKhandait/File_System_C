#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/Global.h"
#include "../header/create_file_system.h"
#include "../header/I_O_operation.h"
#include "../header/bit_map.h"


// Setting the Start of MetaData
    void seek_start_MetaData(){
        if(fseek(DISK,SB.start_MetaData,SEEK_SET) == -1){
            perror("Error in setting the file pointer for MetaData");
            exit(EXIT_FAILURE);
        }
    }

    // Seek MetaData at particular number
    void seek_at_MetaData(unsigned long long int MetaData_num) {
        
        // Jumping to that particular MetaData Block
        unsigned long long int jump = SB.start_MetaData;
        jump = jump + size_MetaData*MetaData_num;

        if(fseek(DISK,jump,SEEK_SET) == -1){
            perror("Error in setting the file pointer for MetaData");
            exit(EXIT_FAILURE);
        }
    }

// Setting the Start of DiskBlock
    void seek_start_DisBlock(){
        if(fseek(DISK,SB.start_Data_Block,SEEK_SET) == -1){
            perror("Error in setting the file pointer for Diskblock");
            exit(EXIT_FAILURE);
        }
    }

    // Seek MetaData at particular number
    void seek_at_DiskBlock(unsigned long long int DiskBlock_num)
    {

        // Jumping to that particular MetaData Block
        unsigned long long int jump = SB.start_Data_Block;
        jump = jump + size_DiskBlock*DiskBlock_num;

        if(fseek(DISK,jump,SEEK_SET) == -1){
            perror("Error in setting the file pointer for DiskBlock");
            exit(EXIT_FAILURE);
        }
    }

// Updating the MetaData
    void update_MetaData(unsigned long long int MetaData_num,struct MetaData *tempMD){

        // Seek at MetaData number
        seek_at_MetaData(MetaData_num);

        // Writing the MetaData Block
        fwrite(tempMD,sizeof(struct MetaData),1,DISK);
    }

// Updating the DiskBlock
    void update_DiskBlock(unsigned long long int DiskBlock_num, struct DiskBlock *tempDB) {

        // Seek at DiskBlock at number
        seek_at_DiskBlock(DiskBlock_num);

        // Writing the DiskBlock
        fwrite(tempDB,size_DiskBlock,1,DISK);
    }

// Allocating the Space
    void allocate_space(unsigned long long int file_size,char *file_name, FILE *file){

        // Find the number of blocks needed
        unsigned long long int count_DiskBlock = file_size + BLOCKSIZE - 1;
        count_DiskBlock = count_DiskBlock/BLOCKSIZE;
        
        // Find the empty MetaData
            unsigned long long int empty_MetaData = search_empty_MetaData();
            if (empty_MetaData == -1)
            {
                perror("\nUnable find the empty DiskBlock");
                exit(1);
            }
            // Updating the bitmap of MetaData
            clear_bit_MetaData(empty_MetaData);

        // Find the All empty DiskBlock
            unsigned long long int *arr_empty_DiskBlock = NULL;
            arr_empty_DiskBlock = malloc(sizeof(unsigned long long int)*count_DiskBlock);
            range_empty_DiskBlock(arr_empty_DiskBlock,count_DiskBlock);

        // Updating the MetaData on Disk
            struct MetaData tempMD;
            strcpy(tempMD.file_name,file_name);
            tempMD.file_number = arr_empty_DiskBlock[0];
            tempMD.file_size = file_size;
            tempMD.first_block = arr_empty_DiskBlock[0];
            update_MetaData(empty_MetaData,&tempMD);

        // Inserting the data into to disk
            // temp struct of DiskBlock
            struct DiskBlock tempDB;
        
            // temp
            char data[BLOCKSIZE];
        
            // File seek to 0
            if(fseek(file,0,SEEK_SET) == -1){
                perror("Unable to Seek Input file");
                exit(EXIT_FAILURE);
            }

            for (unsigned long long int i = 0; i<count_DiskBlock;i++){

                // Next pointer 
                if (i+1 == count_DiskBlock) {
                    tempDB.Next_Disk_Block = -2;
                }
                else{
                    tempDB.Next_Disk_Block = i+1;
                }

            // Input read
            tempDB.pos = fread(data,1,BLOCKSIZE,file);
            
            for (int i = 0; i < tempDB.pos; i++)
            {
                tempDB.Data[i] = data[i];
            }

            //Updating the disk
            update_DiskBlock(arr_empty_DiskBlock[i],&tempDB);
            clear_bit_DiskBlock(arr_empty_DiskBlock[i]);
        }
    }

// Inserting file
void insert_file() {

    // Inputing the file name
        char input_name[NAME];
        printf("\nInput File Name you Insert: ");
        input_string(input_name);

        // Calculating the input file size
        FILE* input_file = fopen(input_name,"r");
        
        if (input_file == NULL)
        {
            perror("\nFile does not exist");
            exit(1);
        }

        fseek(input_file,0,SEEK_END);
        unsigned long long int input_file_size = ftell(input_file);
        if (input_file_size == 0)
        {
            perror("File is Empty");
            exit(1);
        }
        printf("\nInput file size: %llu Bytes\n",input_file_size);

        //Checking is space is available or not
        space_finder();
        if (input_file_size > Space)
        {
            printf("\n Insufficient Space\n");
            exit(1);
        }

        // Allocating the block and metadata to files
        allocate_space(input_file_size,input_name,input_file);
        fclose(input_file);
    }

// Read MetaData
void read_MetaData(struct MetaData *tempMD,unsigned long long int number){
        // Seek at number
        seek_at_MetaData(number);
        // read Block
        fread(tempMD,sizeof(struct MetaData),1,DISK);
    }

// Read DiskBlock
void read_DiskBlock(struct DiskBlock *tempDB,unsigned long long int number){

        // Seek at number
        seek_at_DiskBlock(number);
        // read Block
        fread(tempDB,sizeof(struct DiskBlock),1,DISK);
    }

// Deleting file
void delete_file() {

// Inputing the file_name
    char input_name[NAME];
    printf("\nEnter the File name you want to delete: ");
    input_string(input_name);

// Finding the file in disk
    unsigned long long int arr_MetaData[map_size_MetaData];
    unsigned long long int iterator;
    iterator = find_all_occupied(arr_MetaData);
    struct MetaData tempMD;
    unsigned long long int file_num;
    int flag = 0;

    // Check if the file exist
    for (unsigned long long int i = 0; i < iterator; i++)
    {
        read_MetaData(&tempMD,arr_MetaData[i]);
        if (strcmp(tempMD.file_name,input_name) == 0)
        {
            file_num = arr_MetaData[i];
            flag = 1; 
        }
        else {
            continue;
        }
    }
    if (flag == 0)
    {
        perror("File is Does not exist");
        exit(EXIT_FAILURE);
    }
    
// Empty the MetaBlock
    unsigned long long int DiskBlock_number = tempMD.first_block;
    strcpy(tempMD.file_name,"Empty");
    tempMD.file_number = -1;
    tempMD.file_size = 0;
    tempMD.first_block = -1;
    update_MetaData(file_num,&tempMD); 
    set_bit_MetaData(file_num);
    
// Empty the DiskBlock
    struct DiskBlock tempDB;
    unsigned long long int current = DiskBlock_number;
    unsigned long long int next;

    // Case 1: Contains more than 1 block  
    while(current != -2) {
        // Find the next 
            read_DiskBlock(&tempDB,current);
            next = tempDB.Next_Disk_Block;

        // Empty the current
            tempDB.Next_Disk_Block = -1;
            tempDB.pos = 0;
            strcpy(tempDB.Data,"DummyData");
            update_DiskBlock(current,&tempDB);
            set_bit_DiskBlock(current);

        // updating the current
            current = next;
    }
    printf("\nFile Successfully Deleted!\n");
}

// Read file
void read_file() {

    // Input the file name
        char input_name[NAME];
        printf("\nEnter Filename you want to Read: ");
        input_string(input_name);
    
    // Check if file exist
        // Searching in the disk
        unsigned long long int *arr_MetaData;
        arr_MetaData = malloc(sizeof(unsigned long long int)*map_size_MetaData);
        unsigned long long int iterator;
        iterator = find_all_occupied(arr_MetaData);
        
        struct MetaData tempMD;
        unsigned long long int file_size;
        unsigned long long int first_block;
        int flag = 0;

        // Check if the file exist
        for (unsigned long long int i = 0; i < iterator; i++)
        {
            read_MetaData(&tempMD,arr_MetaData[i]);
            if (strcmp(tempMD.file_name,input_name) == 0)
            {
                // file_num = arr_MetaData[i];
                file_size = tempMD.file_size;
                first_block = arr_MetaData[i];
                flag = 1;
                break;
            }
            else {
                continue;
            }
        }
        if (flag == 0)
        {
            perror("File is Does not exist");
            exit(EXIT_FAILURE);
        }
    
    // Input the output file name
    char output_name[NAME];
    printf("\nEnter the Output file name: ");
    input_string(output_name);
    
    // Creating the output file
    FILE *out = fopen(output_name,"w+");
  
    if (out == NULL)
    {
        perror("Unable open file");
        exit(1);
    }

    
    // Writing into the output file
        struct DiskBlock tempDB;
        unsigned long long int count = file_size + BLOCKSIZE - 1;
        count = count/BLOCKSIZE;
        unsigned long long int next = first_block;
        
        // File seek to 0
        if(fseek(out,0,SEEK_SET) == -1){
                perror("Unable to Seek Input file");
                exit(EXIT_FAILURE);
        }
        
        for(unsigned long long int i = 0; i< count; i++){
            read_DiskBlock(&tempDB,next);
            char data[tempDB.pos];            
            fwrite(tempDB.Data,1,tempDB.pos,out);
            next = tempDB.Next_Disk_Block;
        }
    fclose(out);
}

// Print the All the file in the Disk
void print_files_in_Disk() {

    // Find all the occupied MetaData
        // Searching in the disk
        unsigned long long int *arr_MetaData;
        arr_MetaData = malloc(sizeof(unsigned long long int)*map_size_MetaData);
        unsigned long long int iterator = 0;
        iterator = find_all_occupied(arr_MetaData);

        printf("\nIterator: %llu\n",iterator);

    // Print them
    struct MetaData tempMD;
    printf("\nList of Files: \n");
    for (unsigned long long int i = 0; i < iterator; i++)
    {
        read_MetaData(&tempMD,arr_MetaData[i]);
        printf("\n%llu:\n",i);
        printf("\t File Name: %s\n",tempMD.file_name);
        printf("\t File Size: %llu:\n",tempMD.file_size);
    }
    
}