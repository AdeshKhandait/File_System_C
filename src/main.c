#include<stdio.h>
#include<stdlib.h>
#include "../header/create_file_system.h"
#include "../header/bit_map.h"
#include "../header/file_handling.h"


int main() {
        
        create_file_system();
        insert_file();
        print_bit_block_MetaData(0);
        print_bit_block_DiskBlock(0);
        // clear_bit_DiskBlock(1);
        // clear_bit_MetaData(1);
        // print_bit_block_DiskBlock(0);
        // print_bit_block_MetaData(0);
        // insert_file();
        // print_bit_block_DiskBlock(0);
        // print_bit_block_MetaData(0);
        // read_file_system(47);
    return 0;
}