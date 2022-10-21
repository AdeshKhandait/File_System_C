// Header File related to the Creating the file system

//-------------------------------------------------------------------Variables-------------------------------------------------------

// Defining the MetaData Variables

// Size of sizeHDD
extern unsigned long long int sizeHDD;

// Size of Start Block
extern unsigned long long int size_StartBlock;

// HDD - Size of Start_Block
extern unsigned long long int sizeHDD_StartBlock;

// Size of the MetaData
extern unsigned long long int size_MetaData;

// Size of the DiskBlock
extern unsigned long long int size_DiskBlock;

// MetaData + DiskBlock
extern unsigned long long int size_MetaData_DiskBlock;

// Number of MetaData
extern unsigned long long int num_MetaData;

// Number of the DiskBlock
extern unsigned long long int num_DiskBlock;

// Availabel Space
extern unsigned long long int Space;

//-------------------------------------------------------------------Declaring the Structures-------------------------------------------------------

extern struct StartBlock SB;



// Creating the File System
void create_file_system();

// Reading the File System
void read_file_system(int input);

// Formating the File System
void format_file_system();

// Mounting the file system
void mount_file_system();

// Closing the File system
void closing_file_system();