
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


//-------------------------------------------------------------------Bit Map-------------------------------------------------------

extern __uint128_t *BitMap_MetaData;
extern __uint128_t *BitMap_DiskBlock;
extern int BIT_BLOCK;
extern unsigned long long int map_size_MetaData;
extern unsigned long long int map_size_DiskBlock;
//-------------------------------------------------------------------Function of Create File System-------------------------------------------------------

// Creating the File System
void create_file_system();

// Reading the File System
void read_file_system(int input);

// Print the MetaData
void print_sp_MetaData(unsigned long long int number);

// Print the Diskblock
void print_sp_DiskBlock(unsigned long long int number);

// Formating the File System
void format_file_system();

// Mounting the file system
void mount_file_system();

// Closing the File system
void closing_file_system();

// Printing File System Details
void print_file_system_details();

// Finding the space
void space_finder();
