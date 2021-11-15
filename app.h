#ifndef APP_H
#define APP_H

struct linkLayer
{
    char port[20]; /*Dispositivo /dev/ttySx, x = 0, 1*/
    int baudRate;                  /*Velocidade de transmissão*/
    unsigned int sequenceNumber;   /*Número de sequência da trama: 0, 1*/
    unsigned int timeout;          /*Valor do temporizador: 1 s*/
    unsigned int numTransmissions; /*Número de tentativas em caso de
falha*/
};

struct linkLayer link_info;

int create_data_package(int length, char*data,char*package);
int read_data_package(char* data,char* package);
int create_control_package(int c,char* file_name, int length, char*package);
int read_control_package();

#endif
