#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/Global.h"
#include "../header/create_file_system.h"
#include "../header/I_O_operation.h"
#include "../header/bit_map.h"



// Allocating the Space



// Inserting file
void insert_file() {

    // inputing the file name
        char input_name[NAME];
        input_string(input_name);

        // Calculating the input file size
        FILE *input_file = fopen(input_name,"r");
        
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

            // Setting the MetaData Bit
            clear_bit_MetaData(empty_MetaData);

            printf("\nMetaData: %llu\n",empty_MetaData);
        
        // Finding the Empty DiskBlock
            unsigned long long int empty_DiskBlock = search_empty_DiskBlock();
                if (empty_DiskBlock == -1)
                {
                    perror("Unable Search DiskBlock");
                    exit(1);
                }

            // Setting the DiskBlock Bit
            clear_bit_DiskBlock(empty_DiskBlock);

            printf("\nDiskBlock: %llu\n",empty_DiskBlock);
    
        // 
    
    
    }

