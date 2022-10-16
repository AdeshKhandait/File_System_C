#include<stdio.h>
#include<stdlib.h>
#include "../header/create_file_system.h"
#include "../header/bit_map.h"

int main() {
    
    create_file_system();
    print_bit_block_DiskBlock(0);
    print_bit_block_MetaData(0);
    closing_file_system();
    mount_file_system();
    print_bit_block_DiskBlock(0);
    print_bit_block_MetaData(0);
    closing_file_system();
    return 0;
}