#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Global.h"
#include "../header/create_file_system.h"
#include <unistd.h>

// Assuming
// 1 : Free DiskBlock
// 0 : Occupied DiskBlock
// Zero Indexing

#define SET_BIT(BF, N) BF |= ((__uint128_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((__uint128_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF>>N) & 01)

// MetaData
    // Set all bit
    void set_all_bit_MetaData() {

        for (unsigned long long int i = 0; i < map_size_MetaData; i++)
        {
            BitMap_MetaData[i] = -1;
        }
    }

    // Check is all bit is Set
    void check_all_bit_set_MetaData() {

        for (unsigned long long int i = 0; i < map_size_MetaData; i++)
        {
            if (BitMap_MetaData[i] != -1)
            {
                printf("\n%llu BIT BLOCK of MetaData is not set\n",i);
                exit(1);
            }
        }
    }

    // Creating the Empty Setted Bit
    void create_empty_bit_map_MetaData(){

        // Find the number bit required for MetaData
        map_size_MetaData = num_MetaData/BIT_BLOCK + 1;
        printf("Map Size: %llu\n",map_size_MetaData);

        BitMap_MetaData = malloc(sizeof(__uint128_t)*map_size_MetaData);


        // Set all bit to 1
        set_all_bit_MetaData();

        // Check is all bit is set
        check_all_bit_set_MetaData();


    }

    // printing the Bit Block
    void print_bit_block_MetaData(unsigned long long int number) {

        printf("\nNumber %llu: ",number);
        for (int i = 0; i < BIT_BLOCK; i++)
        {
            if(IS_BIT_SET(BitMap_MetaData[number],i)){
               printf("+"); 
            }
            else{
                printf(".");
            }
        }
        printf("\n");
    }

    // Clear bit of MetaData
    void clear_bit_MetaData(unsigned long long int number) {

        __uint128_t Index = number/ BIT_BLOCK;

        __uint128_t Bit_num = number % BIT_BLOCK;

        CLR_BIT(BitMap_MetaData[Index],Bit_num);
    }

    // Setting bit of MetaDat
    void set_bit_MetaData(unsigned long long int number) {

        __uint128_t Index = number/BIT_BLOCK;
        __uint128_t Bit_num = number % BIT_BLOCK;
        SET_BIT(BitMap_MetaData[Index],Bit_num);
    }


// DiskBlock

    // Set all bit
    void set_all_bit_DiskBlock() {

        for (unsigned long long int i = 0; i < map_size_DiskBlock; i++)
        {
            BitMap_DiskBlock[i] = -1;
        }
    }

    // Check is all bit is Set
    void check_all_bit_set_DiskBlock() {

        for (unsigned long long int i = 0; i < map_size_DiskBlock; i++)
        {
            if (BitMap_DiskBlock[i] != -1)
            {
                printf("\n%llu BIT BLOCK of DiskBlock is not set\n",i);
                exit(1);
            }
        }
    }

    // Creating the Empty Setted Bit
    void create_empty_bit_map_DiskBlock(){

        // Find the number bit required for MetaData
        map_size_DiskBlock = num_DiskBlock/BIT_BLOCK + 1;
        printf("Map Size: %llu\n",map_size_DiskBlock);

        BitMap_DiskBlock = malloc(sizeof(__uint128_t)*map_size_DiskBlock);

        // Set all bit to 1
        set_all_bit_DiskBlock();

        // Check is all bit is set
        check_all_bit_set_DiskBlock();


    }

    // printing the Bit Block
    void print_bit_block_DiskBlock(unsigned long long int number) {

        printf("\nNumber %llu: ",number);
        for (int i = 0; i < BIT_BLOCK; i++)
        {
            if(IS_BIT_SET(BitMap_DiskBlock[number],i)){
               printf("+"); 
            }
            else{
                printf(".");
            }
        }
        printf("\n");
    }

    // Clear bit of MetaData
    void clear_bit_DiskBlock(unsigned long long int number) {

        __uint128_t Index = number/ BIT_BLOCK;

        __uint128_t Bit_num = number % BIT_BLOCK;

        CLR_BIT(BitMap_DiskBlock[Index],Bit_num);
    }

    // Setting bit of MetaDat
    void set_bit_DiskBlock(unsigned long long int number) {

        __uint128_t Index = number/BIT_BLOCK;
        __uint128_t Bit_num = number % BIT_BLOCK;
        SET_BIT(BitMap_DiskBlock[Index],Bit_num);
    }