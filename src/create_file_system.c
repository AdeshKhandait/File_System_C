#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/Global.h"
#include "../header/I_O_operation.h"

//-------------------------------------------------------------------Variables-------------------------------------------------------

// Defining the MetaData Variables

// Size of sizeHDD
unsigned long long int sizeHDD;

// Size of Start Block
unsigned long long int size_StartBlock;

// HDD - Size of Start_Block
unsigned long long int sizeHDD_StartBlock;

// Size of the MetaData
unsigned long long int size_MetaData;

// Size of the DiskBlock
unsigned long long int size_DiskBlock;

// MetaData + DiskBlock
unsigned long long int size_MetaData_DiskBlock;

// Number of MetaData
unsigned long long int num_MetaData;

// Number of the DiskBlock
unsigned long long int num_DiskBlock;

unsigned long long int Space;

//-------------------------------------------------------------------Declaring the Structures-------------------------------------------------------

struct StartBlock SB;

// Creating the File System
void create_file_system() {
//-------------------------------------------------------------------File System Size-------------------------------------------------------

    // Inputing the size of disk
    printf("\nEnter the Size of Hard Disk in GB: ");
    sizeHDD = input_sizeHDD();
    // printf("\nSizeHDD : %llu\n",sizeHDD);

    // Converting into Bytes
    sizeHDD = sizeHDD * 1000000000;
    // printf("\nSize in GB: %llu\n",sizeHDD);

    // Size of StartBlock
    size_StartBlock = sizeof(struct StartBlock);
    // printf("\nSize of StartBlock: %llu\n",size_StartBlock);

    // SizeHDD - StartBlock
    sizeHDD_StartBlock = sizeHDD - size_StartBlock;
    // printf("\nSize of SizeHDD - StartBlock: %llu\n",sizeHDD_StartBlock);

    // Size of MetaBlock
    size_MetaData = sizeof(struct MetaData);
    // printf("\nSize of MetaBlock: %llu\n",size_MetaData);

    // Size of DiskBlock
    size_DiskBlock = sizeof(struct DiskBlock);
    // printf("\nSize of DiskBlock: %llu\n",size_DiskBlock);

    // sizeof MetaData + DiskBlock
    size_MetaData_DiskBlock = size_MetaData + size_DiskBlock;
    // printf("\nSize of the MetaBlock + DiskBlock: %llu\n",size_MetaData_DiskBlock);

    // Num of MetaData
    num_MetaData = sizeHDD_StartBlock / size_MetaData_DiskBlock;
    // printf("\nNum MetaData: %llu\n",num_MetaData);

    // Num of DiskBlock
    num_DiskBlock = num_MetaData;
    // printf("\nNum of DiskBlock: %llu\n",num_DiskBlock);

//-------------------------------------------------------------------Creating File System-------------------------------------------------------

// Creating the disk
    create_disk();

// Writing the StartBlock
    SB.sizeHDD = sizeHDD;
    // printf("\nSizeHDD: %llu\n",SB.sizeHDD);
    SB.size_block = BLOCKSIZE;
    // printf("\nBlock Size: %lu\n",SB.size_block);
    SB.start_MetaData = size_StartBlock;
    // printf("\nStart of MetaData: %llu\n",SB.start_MetaData);
    SB.start_Data_Block = (size_MetaData * num_MetaData) + size_StartBlock;
    // printf("\nStart of Data Block: %llu\n",SB.start_Data_Block);
    fwrite(&SB,size_StartBlock,1,DISK);

// Writing the MetaData
    struct MetaData MetaData_Buffer;
    // Setting the MetaData
    MetaData_Buffer.file_number = -1;
    MetaData_Buffer.file_size = 0;
    MetaData_Buffer.first_block = -1;
    strcpy(MetaData_Buffer.file_name,"Empty");
    for (unsigned long long int i = 0; i < num_MetaData; i++)
    {
        fwrite(&MetaData_Buffer,sizeof(struct MetaData),1,DISK);
    }

// Writing the DiskBlock
    struct DiskBlock Block;
    // Setting the DiskBlock
    Block.Next_Disk_Block = -1;
    Block.pos = 0;
    strcpy(Block.Data,"DummyData");
    for (unsigned long long int i = 0; i < num_DiskBlock; i++)
    {
        fwrite(&Block,sizeof(struct DiskBlock),1,DISK);
    }

printf("\nFile System Successfully Created!\n");
}

// Reading the File System
void read_file_system(int input){


// StartBlock
    struct StartBlock tempSb;
    fseek(DISK,0,SEEK_SET);
    fread(&tempSb,size_StartBlock,1,DISK);
    printf("\nSizeHDD: %llu\n",tempSb.sizeHDD);
    printf("\nBlock Size: %lu\n",tempSb.size_block);
    printf("\nStart of MetaData: %llu\n",tempSb.start_MetaData);
    printf("\nStart of Data Block: %llu\n",tempSb.start_Data_Block);


// MetaData 
    struct MetaData tempMD;
    fseek(DISK,SB.start_MetaData,SEEK_SET);
    printf("\nMetaData:\n");
    for (int i = 0; i < input; i++)
    {   
        fread(&tempMD,size_MetaData,1,DISK);
        printf("\n%d:\n",i);
        printf("\tFile Size: %llu\n",tempMD.file_size);
        printf("\tFirst Block: %lld\n",tempMD.first_block);
        printf("\tFile number: %lld\n",tempMD.file_number);
        printf("\tFile Name: %s\n",tempMD.file_name);    
    }


// DiskBlock 
    struct DiskBlock tempDB;
    fseek(DISK,SB.start_Data_Block,SEEK_SET);
    printf("\nDiskBlock:\n");
    for (int i = 0; i < input; i++)
    {   
        fread(&tempDB,sizeof(struct DiskBlock),1,DISK);
        printf("\n%d:\n",i);
        printf("\tNext Block: %lld\n",tempDB.Next_Disk_Block);
        printf("\tPos : %ld\n",tempDB.pos);   
    }
}

// Formating the File System
void format_file_system() {
    
    // Closing the Existing file
    fclose(DISK);
    // Creating the New File
    create_disk();
// Reading the disk Size
    
    // Writing the StartBlock
        SB.sizeHDD = sizeHDD;
        // printf("\nSizeHDD: %llu\n",SB.sizeHDD);
        SB.size_block = BLOCKSIZE;
        // printf("\nBlock Size: %lu\n",SB.size_block);
        SB.start_MetaData = size_StartBlock;
        // printf("\nStart of MetaData: %llu\n",SB.start_MetaData);
        SB.start_Data_Block = (size_MetaData * num_MetaData) + size_StartBlock;
        // printf("\nStart of Data Block: %llu\n",SB.start_Data_Block);
        fwrite(&SB,size_StartBlock,1,DISK);

    // Writing the MetaData
        struct MetaData MetaData_Buffer;
        // Setting the MetaData
        MetaData_Buffer.file_number = -1;
        MetaData_Buffer.file_size = 0;
        MetaData_Buffer.first_block = -1;
        strcpy(MetaData_Buffer.file_name,"Empty");
        for (unsigned long long int i = 0; i < num_MetaData; i++)
        {
            fwrite(&MetaData_Buffer,sizeof(struct MetaData),1,DISK);
        }

    // Writing the DiskBlock
        struct DiskBlock Block;
        // Setting the DiskBlock
        Block.Next_Disk_Block = -1;
        Block.pos = 0;
        strcpy(Block.Data,"DummyData");
        for (unsigned long long int i = 0; i < num_DiskBlock; i++)
        {
            fwrite(&Block,sizeof(struct DiskBlock),1,DISK);
        }
    printf("\nFile System Clean Successfully!\n");
}

// Mounting the File System
void mount_file_system() {

    // Mounting the file system
    DISK = fopen(DISK_NAME,"a+");
    // Setting the file pointer to start
    fseek(DISK,0,SEEK_SET);
    printf("\nFile System Successfully Mounted!\n");
}

// Closing the File system
void closing_file_system(){
    // Closing the file system
    fclose(DISK);
    printf("\nFile System Close Successfully!\n");
}