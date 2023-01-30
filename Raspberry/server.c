#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <wiringPi.h>
#include <ctype.h>

#define SA struct sockaddr
#define RED 29
#define GREEN 28
#define YELLOW 27
 
int IsNumber(int argc, char *argv[]);
int WiringPi();
char *Temp();
void Lamps(char array[]);


int main(char argc, char *argv[])
{
    // port check
    if(IsNumber(argc, argv) == -1)     
        exit(0);
    
    // Initialize WiringPi 
    if(WiringPi() == -1)     
        exit(0);
   
    
    // Server code 
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    
    // Create - IPv4 and TCP 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket failed...\n");
        exit(0);
    }
    else
        printf("Socket created...\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // Server settings 
    servaddr.sin_family = AF_INET; //IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // default
    servaddr.sin_port = htons(atoi(argv[1])); // port number

   
    // Bind
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Bind failed...\n");
        exit(0);
    }
    else
        printf("Bind success...\n");
   
   
    // Listen
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Listening...\n");
    len = sizeof(cli);
   
    // Accept
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed...\n");
        exit(0);
    }
    else
        printf("Server accept the client...\n");
   
    // Write and Read 
    int n = 0;
    while(1){
        char color[3], buff[5];
        
        //temperature measure
        char *array = Temp();
        printf("\n%d.\ntemp RaspberryPi: ",n++);
        
        //write
        bzero(buff, 5);
        for(int i = 0; i < 5; i++){
            printf("%c",*(array+2+i));
            buff[i] = *(array+2+i);
        }printf("\n");
    
        write(connfd, buff, sizeof(buff));
    
        //read
        bzero(color, 3);
        read(connfd, color, sizeof(color));
        Lamps(color);
        
  
        sleep(0.1);
    }
    
    // Close
    close(sockfd);
    printf("Socket closed\n");
    
    return 0;
}


int IsNumber(int argc, char *argv[]){
     if(argc != 2){
        printf("Wrong input!\n");
        return -1;
    }
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++){
        if (!isdigit(argv[1][i])){
            printf("Not a port number!\n");
            return -1;
        }
    }
    printf("Port: %d\n",atoi(argv[1]));
    return 0;
}

int WiringPi(){
    if(wiringPiSetup() == -1)	//initialize WiringPi  
		return -1;
    
    pinMode(RED,OUTPUT);
    pinMode(YELLOW,OUTPUT);
    pinMode(GREEN,OUTPUT);

    return 0;
}

char * Temp(){
    FILE *thermometer;
    static char data[7];

    thermometer = fopen("/sys/bus/w1/devices/28-0000084b3a18/w1_slave","r");
    if (thermometer == NULL){
        printf("ERROR: DS18B20 not found!");
        return 0;
	}
 
    while (fscanf(thermometer,"%s",data) != EOF);
    fclose(thermometer);

    return data;
}   

void Lamps(char array[]){
    printf("Bits received:\n");
    for(int i = 0; i< 3; i++)
        printf("color[%d]:%d\n",i,array[i]);
    printf("\n");
            
    if (array[0] == 0){
        digitalWrite(GREEN,LOW);
        printf("GREEN: OFF\n");
    }
    else if (array[0] == 1){
        digitalWrite(GREEN,HIGH);
        printf("GREEN: ON\n");
    }
    if (array[1] == 0){
        digitalWrite(YELLOW,LOW);
        printf("YELLOW: OFF\n");
    }
    else if (array[1] == 1){
        digitalWrite(YELLOW,HIGH);
        printf("YELLOW: ON\n");
    }
    if (array[2] == 0){
        digitalWrite(RED,LOW);
        printf("RED: OFF\n");
    }
    else if (array[2] == 1){
        digitalWrite(RED,HIGH);
        printf("RED: ON\n");
    }   
    
}
