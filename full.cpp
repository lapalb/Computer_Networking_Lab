#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int frameSender[65], frameRecver[65], ackSender[65], ackRecver[65];
int lSenderS, rSenderS, lSenderR, rSenderR;
int lRecverS, rRecverS, lRecverR, rRecverR;
int n;

void *chkSender(void *args) {
    int id = (*(int *)args);
    while (!ackSender[id]);
    if (rRecverR != n) rRecverR++;
    pthread_exit(NULL);
}

void *chkRecver(void *args) {
    int id = (*(int *)args);
    while (!ackRecver[id]);
    if (rSenderR != n) rSenderR++;
    pthread_exit(NULL);
}

void *sendS(void *args) {
    pthread_t chkAck;
    while (1) {
        if (lSenderS <= rSenderS) {
            cout << "Sender 1 sent frame: " << lSenderS << "\n";
            frameSender[lSenderS] = 1;
            usleep(4000000);
            int i = lSenderS;
            pthread_create(&chkAck, NULL, chkSender, (void *)&i);
            lSenderS++;
        }
        if (lSenderS > n) break;
    }
    pthread_exit(NULL);
}

void *sendR(void *args) {
    while (1) {
        if (lSenderR <= rSenderR) {
            while (!frameRecver[lSenderR]);
            cout << "Sender 1 acknowledged frame: " << lSenderR << "\n";
            ackRecver[lSenderR] = 1;
            usleep(3000000);
            lSenderR++;
            if (rRecverS != n) rRecverS++;
        }
        if (lSenderR > n) break;
    }
    pthread_exit(NULL);
}

void *recvS(void *args) {
    pthread_t chkAck;
    while (1) {
        if (lRecverS <= rRecverS) {
            cout << "Sender 2 sent frame: " << lRecverS << "\n";
            frameRecver[lRecverS] = 1;
            usleep(5000000);
            int i = lRecverS;
            pthread_create(&chkAck, NULL, chkRecver, (void *)&i);
            lRecverS++;
        }
        if (lRecverS > n) break;
    }
    pthread_exit(NULL);
}

void *recvR(void *args) {
    while (1) {
        if (lRecverR <= rRecverR) {
            while (!frameSender[lRecverR]);
            cout << "Sender 2 acknowledged frame: " << lRecverR << "\n";
            ackSender[lRecverR] = 1;
            usleep(2000000);
            lRecverR++;
            if (rSenderS != n) rSenderS++;
        }
        if (lRecverR > n) break;
    }
    pthread_exit(NULL);
}

int main() {
    int totFrames = 12;
    n = totFrames;
    int window = 4;
    lSenderS = lRecverR = lSenderR = lRecverS = 1;
    rSenderS = rRecverR = rSenderR = rRecverS = 4;
    pthread_t sendThreadS, sendThreadR, recvThreadS, recvThreadR;
    pthread_create(&sendThreadS, NULL, sendS, NULL);
    pthread_create(&sendThreadR, NULL, sendR, NULL);
    pthread_create(&recvThreadS, NULL, recvS, NULL);
    pthread_create(&recvThreadR, NULL, recvR, NULL);
    pthread_join(sendThreadS, NULL);
    pthread_join(sendThreadR, NULL);
    pthread_join(recvThreadS, NULL);
    pthread_join(recvThreadR, NULL);
    return 0;
}
