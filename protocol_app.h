#ifndef PROTOCOL_APP_H
#define PROTOCOL_APP_H

int llopen(char* porta,int sender);
int llwrite(int fd, char*buffer,int length);
int llread(int fd,char*buffer);
int llclose(int fd, int sender);

#endif