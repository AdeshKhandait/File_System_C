#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/Global.h"




// Inputing the unsigned long long int
unsigned long long int input_sizeHDD() {

    unsigned long long int input;
    // restricting to 1 digit and 10 GB
    scanf("%llu",&input);
    getchar();
    return input;
    
    
}

// Creating the Disk 
void create_disk(){

    DISK = fopen(DISK_NAME,"w+");
    if (DISK == NULL)
    {
        perror("Unable open Disk");
        exit(1);
    }
}

// Inputing the string
void input_string(char *input) {

        // printf("\nInput the String: ");
        scanf("%s",input);
        
        if (strlen(input) == 0)
        {
            perror("String is empty!");
            exit(1);
        }
    }


