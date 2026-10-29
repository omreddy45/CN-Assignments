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

    int totalHop = sizeof(hop)/sizeof(hop[0]);

    int receiverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in receiverAddress, transmitterAddress;
    socklen_t len = sizeof(transmitterAddress);

    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(9000);
    receiverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(receiverSocket, (struct sockaddr *)&receiverAddress, sizeof(receiverAddress));

    for(int i=0; i<7; i++) {

        int tuned = freq[hop[i%totalHop]];

        struct packet p;
        recvfrom(receiverSocket, &p, sizeof(p), 0, (struct sockaddr *)&transmitterAddress, &len);

        if(p.freq == tuned)
            printf("Tuned to %d MHz, Received: %s\n", tuned, p.data);
        else
            printf("Tuned to %d MHz, packet on %d MHz ignored\n", tuned, p.freq);
    }

    close(receiverSocket);
    return 0;
}
