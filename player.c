#include "message.h"

int main() {
    int port = PORT;
    int s;
    struct sockaddr_in addr;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 0;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(s, (struct sockaddr *)&addr, sizeof addr) < 0) {
        perror("connect");
        return 0;
    }
    printf("ゲームマスターと接続しました.\n");
    srand((unsigned)time(NULL));
    struct Message msg;
    msg.loseflag = -1;
    while (1) {
        struct timeval start, end;
        if (recv(s, &msg, sizeof msg, 0) < 0) {
            perror("recv");
            return 0;
        }
        if (!msg.loseflag) {
            printf("相手が空振りしました.あなたの勝ちです!\n");
            return 0;
        }
        printf("!!");
        char buf[DATA_SIZE];
        gettimeofday(&start, NULL);
        fgets(buf, DATA_SIZE, stdin);
        gettimeofday(&end, NULL);
        double sec = (double)(end.tv_sec - start.tv_sec);
        double msec = (double)(end.tv_usec -start.tv_usec);
        double elapsed = sec + msec / 1000 / 1000;
        printf("%f\n", elapsed);
        if (elapsed > msg.time * 1.1)
            break;
        msg.time = elapsed;
        sleep(rand()%10+1);

        if (send(s, &msg, sizeof msg, 0) < 0) {
            perror("send");
            return 0;
        }    
    }
    msg.loseflag = 0;
    if (send(s, &msg, sizeof msg, 0) < 0) {
            perror("send");
            return 0;
    }    
    printf("空振り. あなたの負けです!\n");
}