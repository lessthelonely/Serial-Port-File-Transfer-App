#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "../include/app.h"
#include "../include/constants.h"

/*We are gonna ask the user for stuff to fill out the struct linkLayer 
Need to make two packets: control and data
Control packets have two types: 1) symbolizes transmission start
                                2) symbolizes transmission end
Contents of each packet->slide 23
Packages are sent by TRANSMITTER-->need to make functions to read them? Yeah, probs
*/

/* Return -1 if error, 0 otherwise
*/
int create_data_package(int n, int length, u_int8_t *data, u_int8_t *package)
{
    //ASK TEACHER: check how N, L2 and L1 are calculated
    printf("I'm in create_data_package\n");
    package[0] = CTRL_DATA; //C – campo de controlo (valor: 1 – dados)
    package[1] = n % 255;   //%255->does it only want the sequenceNumber or is it, sequenceNumber % 255
    package[2] = length / 256; //L2
    package[3] = length % 256; //L1
    if (memcpy(&package[4], data, length) == NULL)
    { //memcpy returns destination pointer
        printf("ERROR\n");
        return -1;
    }
    printf("LENGTH %d\n",length);
    //printf("Data package was created");
    return 0;
}

int create_control_package(u_int8_t c, u_int8_t *file_name, int file_size, u_int8_t *package)
{
    //printf("IN CREATE CONTROL PACKAGE\n");
    int size = 0;
    package[0] = c; //need to be informed if it's supposed to be the start (2) or end (3)-->should I make constants?
    /*Going to have two sets of TLV:
    First one is about the size of the file
    Second about the name of the file
    */
    /*printf("PACKAGE[0] %02x\n",package[0]);
    printf("file_size ");
    printf("%d\n", file_size);

    char *lstring = (char *)malloc(sizeof(int));
    sprintf(lstring, "%d", file_size);

    printf("lstring ");
    printf("%s\n", lstring);

    package[1] = 0; //file size (should it be a constant?)
    package[2] = strlen(lstring);
    if (memcpy(&package[3], lstring, strlen(lstring)) == NULL)
    {
        printf("ERROR\n");
        free(lstring);
        return -1;
    }
    size = 3 + strlen(lstring);

    package[size] = 1;
    size++;
    package[size] = strlen(file_name);
    size++;
    if (memcpy(&package[size], file_name, strlen(file_name)) == NULL)
    {
        printf("ERROR\n");
        free(lstring);
        return -1;
    }
    size += strlen(file_name);
    printf("Control package created\n");
    free(lstring);
    return size;*/

     int size_nameFile = strlen(file_name), curr_pos = 0; 
    package[1] = T_FILE_NAME; 
    package[2]= strlen(file_name); 

    if (memcpy(&package[3] , file_name, size_nameFile) == NULL){
        printf("Not possible to copy file name"); 
        return -1; 
    }
    
    curr_pos = 3 + size_nameFile;
    //printf("SIZE CURRENT %d\n",curr_pos);
    char * length_string = (char*)malloc(sizeof(int)); 
    sprintf(length_string, "%d", file_size);                        // Int to string. 

    package[curr_pos] = T_FILE_SIZE;   
    package[curr_pos+1] = strlen(length_string);  

    if (memcpy(&package[curr_pos+2], length_string, strlen(length_string)) == NULL){
        printf("Not possible to copy size of file"); 
        return -1; 
    }

   // printf("Created control package.");  
    int sizeP=curr_pos + strlen(length_string) + 2;
    //printf("SIZE CURRENT %d\n",sizeP);

    /*for(int i =0;i<sizeP;i++){
        printf("P %02x\n",package[i]); //package is full and data is correct
    }*/
    return sizeP;

}

int read_data_package(u_int8_t *data, u_int8_t *package)
{
    /*Okay package[0] doesn't matter here, will matter where we call it tho
    should we change the sequence number to whatever sequence number is in package[1]?
    package[2] & [3] are gonna be used to know the size of the info
    Rest of the package is gonna be copied into char*data because data
*/

    //What if there's more values to sequence number than 0 and 1 and that's why we got the %255 stuff? Idk tbh

    if (package[1] > app_info.sequenceNumber)
    {
        return -1; //repeated packet
    }
    app_info.sequenceNumber = (app_info.sequenceNumber + 1) % 255; //Update

    int size = 256 * package[2] + package[3];
    if (memcpy(data, &package[4], size) == NULL)
    {
        printf("ERROR\n");
        return -1;
    }
    return size;
}

int read_control_package(u_int8_t *package, u_int8_t *file_name, int *file_size, int package_size)
{
    //printf("I'M IN READ CONTROL PACKAGE\n");
    u_int8_t *sizes = (u_int8_t*)malloc(sizeof(int));
    int size;
    /*Idk if package is written differently if C is start or end
    Let's assume it's the same I guess
    I think if it's start, then you send the data package and if it's stop...you don't? Don't really know*/

    for (int i = 1; i < package_size; i++)
    {
        /*printf("Holo\n");
        printf("%02x\n",package[i]);*/
        if (package[i] == T_FILE_SIZE)
        { //file size
           // printf("Inside is cold\n");
            i++;
            size = package[i];
            i++;
            if (memcpy(sizes, &package[i], size) == NULL)
            {
                printf("ERROR\n");
                free(sizes);
                return -1;
            }
            sscanf(sizes, "%d", file_size);
            i += size;
        }
        if (package[i] == T_FILE_NAME)
        { //file name
            i++;
            size = package[i];
            i++;
            if (memcpy(file_name, &package[i], size) == NULL)
            {
                printf("ERROR\n");
                free(sizes);
                return -1;
            }
            i += size-1;
        }
    }
    free(sizes);
    return 0;
}