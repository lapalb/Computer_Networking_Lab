#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int n;
int lSender, rSender;
int lRecver, rRecver;
int frame[65], ack[65];

void *chk(void *args) {
    int id = (*(int *)args);
    while (!ack[id]);
    if (rRecver != n) rRecver++;
    pthread_exit(NULL);
}

void *FrameS(void *args) {
    pthread_t chkAck;
    while (1) {
        if (lSender <= rRecver) {
            cout << "Sending frame: " << lSender << "\n";
            frame[lSender] = 1;
            usleep(1000000);
            int i = lSender;
            pthread_create(&chkAck, NULL, chk, (void *)&i);
            lSender++;
        }
        if (lSender > n) break;
    }
    pthread_join(chkAck, NULL);
    pthread_exit(NULL);
}

void *FrameR(void *args) {
    while (1) {
        if (lRecver <= rRecver) {
            while (!frame[lRecver]);
            cout << "Acknowledged frame: " << lRecver << "\n";
            ack[lRecver] = 1;
            usleep(3000000);
            lRecver++;
            if (rSender != n) rSender++;
        }
        if (lRecver > n) break;
    }
    pthread_exit(NULL);
}

int main() {
    int totFrames = 24;
    int block = 4;
    lSender = lRecver = 1;
    rSender = rRecver = 4;
    n = totFrames;
    cout << "Total frames to send: " << totFrames << "\n";
    cout << "Window size: " << block << "\n";
    pthread_t sendThread, recvThread;
    int sendOk = pthread_create(&sendThread, NULL, FrameS, NULL);
    int recvOk = pthread_create(&recvThread, NULL, FrameR, NULL);
    pthread_join(sendThread, NULL);
    pthread_join(recvThread, NULL);
    pthread_exit(NULL);
    return 0;
}
