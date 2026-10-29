#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

struct packet {
    int freq;
    char data[100];
};

int main() {

    int freq[] = {2400,2401,2402,2403,2404};
    int hop[] = {3,1,0,4,2};

    char *reply[] = {"Hello",", ","My ","name ","is ","Om ","Reddy"};

    int totalHop = sizeof(hop)/sizeof(hop[0]);
    int totalMsg = sizeof(reply)/sizeof(reply[0]);

    int transmitterSocket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in receiverAddress;
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(9000);
    receiverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    for(int i=0; i<totalMsg; i++) {

        struct packet p;
        p.freq = freq[hop[i%totalHop]];
        strcpy(p.data, reply[i]);

        sendto(transmitterSocket, &p, sizeof(p), 0, (struct sockaddr *)&receiverAddress, sizeof(receiverAddress));

        printf("Sent on %d MHz: %s\n", p.freq, p.data);

        sleep(1);
    }

    close(transmitterSocket);
    return 0;
}
