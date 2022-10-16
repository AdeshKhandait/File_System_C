#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/Global.h"

// Inputing the unsigned long long int
unsigned long long int input_sizeHDD() {

    unsigned long long int input;
    // restricting to 1 digit and 10 GB
    scanf("%1llu",&input);
    getchar();
    if (input == 0 || input >=10)
    {
        perror("Invaild Value");
        exit(1);
    }
    else{
        return input;
    }
    
}

// Creating the Disk 
void create_disk(){

    DISK = fopen(DISK_NAME,"w+");
    if (DISK == NULL)
    {
        perror("Unable open Disk");
        exit(1);
    }
    else{
        printf("Disk Open Successfully!\n");
    }
}

// Inputing the string
void input_string(char *input) {

        printf("\nInput the String: ");
        scanf("%s",input);
        
        if (strlen(input) == 0)
        {
            perror("String is empty!");
            exit(1);
        }
    }


