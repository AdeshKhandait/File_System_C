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
    void seek_at_DiskBlock(unsigned long long int DiskBlock_num) {
        
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
    void allocate_space_Data(FILE *input_file,unsigned long long int file_size,unsigned long long int first_Empty_DiskBlock, unsigned long long int **arr_DiskBlock,unsigned long long int *len_DiskBlock){

        // Finding the number of Block need 
        unsigned long long int count_DiskBlock = file_size + BLOCKSIZE - 1;
        count_DiskBlock = count_DiskBlock/BLOCKSIZE;
        *len_DiskBlock = count_DiskBlock;
        // printf("len: %llu",*len_DiskBlock);
        *arr_DiskBlock = malloc(sizeof(unsigned long long int)*count_DiskBlock);
        
        // Temper for Search Empty DiskBlock
        unsigned long long int temp;
        
        // Previous DiskBlock
        unsigned long long int prev = first_Empty_DiskBlock;
        // arr_DiskBlock[0] = prev;
        
        // temper struct for updating
        struct DiskBlock tempDB;
        char input_Data[BLOCKSIZE];

        unsigned long long int buffer = file_size;

        if(fseek(input_file,0,SEEK_SET) == -1){
            perror("Unable to Seek Input file");
            exit(EXIT_FAILURE);
        }

        for (unsigned long long int i = 0; i < count_DiskBlock; i++)
        {
            // Finding the Empty DiskBlock
            temp = search_empty_DiskBlock();
            
            // Updating teh DiskBlock
            clear_bit_DiskBlock(temp);

            if (temp == -1)
            {
                perror("Error in Finding the Empty DiskBlock");
                exit(EXIT_FAILURE);
            }

            //Updating the previous Diskblock
            tempDB.Next_Disk_Block = temp;
            tempDB.pos = BLOCKSIZE - 1;
            fread(input_Data,BLOCKSIZE,1,input_file);
            // printf("%s",input_Data);
            strcpy(tempDB.Data,input_Data);
            (*arr_DiskBlock)[i] = prev;
            // printf("i: %llu\n",arr_DiskBlock[i]);
            update_DiskBlock(prev,&tempDB);

            // upading the previous
            prev = temp;
        }
        
        // Upadint the last BLock
        buffer = file_size % BLOCKSIZE;
        fseek(input_file,file_size-buffer,SEEK_SET);
        char tp[buffer];
        tempDB.Next_Disk_Block = -2;
        tempDB.pos = buffer;
        fread(tp,buffer,1,input_file);
        strcpy(tempDB.Data,tp);
        (*arr_DiskBlock)[*len_DiskBlock] = prev;
        update_DiskBlock(prev,&tempDB);
        // printf("\n%llu Block is successfully Allocated\n",count_DiskBlock);
    }

// Inserting file
void insert_file() {

    // inputing the file name
        char input_name[NAME];
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
        if (input_file_size > Space)
        {
            printf("\n Insufficient Space\n");
            exit(1);
        }
        
        // Finding the Empty MetaData
            unsigned long long int empty_MetaData = search_empty_MetaData();
                if (empty_MetaData == -1)
                {
                    perror("Unable Search MetaData");
                    exit(1);
                }

            // Clearing the MetaData Bit
            clear_bit_MetaData(empty_MetaData);

            // printf("\nMetaData: %llu\n",empty_MetaData);
        
        // Finding the Empty DiskBlock
            unsigned long long int empty_DiskBlock = search_empty_DiskBlock();
                if (empty_DiskBlock == -1)
                {
                    perror("Unable Search DiskBlock");
                    exit(1);
                }

            // Clearing the DiskBlock Bit
            clear_bit_DiskBlock(empty_DiskBlock);

            // printf("\nDiskBlock: %llu\n",empty_DiskBlock);
    
        // Updating the MetaData
         struct MetaData tempMD;
            strcpy(tempMD.file_name,input_name);
            tempMD.file_number = empty_MetaData;
            tempMD.file_size = input_file_size;
            tempMD.first_block = empty_DiskBlock;
            update_MetaData(empty_MetaData,&tempMD);

        // Updating the DiskBlock
            struct DiskBlock tempDB;
            tempDB.Next_Disk_Block = -2;
            tempDB.pos = 0;
            update_DiskBlock(empty_DiskBlock,&tempDB);

        // Allocating the Space
        unsigned long long int *arr_DiskBlock;
        unsigned long long int len_DiskBlock;
        allocate_space_Data(input_file,input_file_size,empty_DiskBlock,&arr_DiskBlock,&len_DiskBlock);
    
        // return file numer
        printf("File Name %s with file_number: %llu is Inserted Succesfully!",input_name,empty_MetaData);
        
    }

// Deleting file
void delete_file() {

    // Inputing the file_name
    char input_name[NAME];
    input_string(input_name);

    



}