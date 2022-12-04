#include<stdio.h>
#include<stdlib.h>
#include "../header/create_file_system.h"
#include "../header/bit_map.h"
#include "../header/file_handling.h"


int main() {



// File system Related Operation

        // Create the file
        create_file_system();
        
        // Format file system
        // format_file_system();

        // Mount file system previously create
        // mount_file_system();

        // Close the file system
        // closing_file_system();

        // Print the file system Details
        // print_file_system_details();

// Operation in File system

        // Inserting the file
        insert_file(); 

        // List all the files in File system
        print_files_in_Disk();

        // Read file
        read_file();

        // delete file
        delete_file();

        // List all the files in File system
        print_files_in_Disk();

    return 0;
}