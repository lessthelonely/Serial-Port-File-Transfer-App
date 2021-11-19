#ifndef APP_H
#define APP_H

struct linkLayer
{
    char port[20];                 /*Dispositivo /dev/ttySx, x = 0, 1*/
    int baudRate;                  /*Velocidade de transmissão*/
    unsigned int sequenceNumber;   /*Número de sequência da trama: 0, 1*/
    unsigned int timeout;          /*Valor do temporizador: 1 s*/
    unsigned int numTransmissions; /*Número de tentativas em caso de
falha*/
};

struct applicationLayer
{
    int fileDescriptor; /*Descritor correspondente à porta série*/
    int status;         /*TRANSMITTER | RECEIVER*/
    int sequenceNumber;
};

struct linkLayer link_info;
struct applicationLayer app_info;

int create_data_package(int n, int length, u_int8_t *data, u_int8_t *package);
int read_data_package(u_int8_t*data, u_int8_t *package);
int create_control_package(int c, char *file_name, int length, u_int8_t*package);
int read_control_package(u_int8_t *package, char *file_name, int *file_size, int package_size);

#endif
