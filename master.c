#include "message.h"

int main() {
    int s;
    struct sockaddr_in my_addr;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 0;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&my_addr, sizeof my_addr) < 0) {
        perror("bind");
        return 0;
    }
    listen(s, 5);
    printf("プレイヤー受付中...\n");
    int s2;
    struct sockaddr_in addr;
    socklen_t sktlen = sizeof addr;
    s2 = accept(s, (struct sockaddr *)&addr, &sktlen);
    printf("プレイヤーを発見しました. ゲームを開始します.\n");

    srand((unsigned)time(NULL));
    char buf[DATA_SIZE];
    struct Message msg;
    msg.loseflag = -1;
    msg.time = 10.0;
    printf("好きなタイミングでEnterを入力してください.>");
    fgets(buf, DATA_SIZE, stdin);
    sleep(rand()%10+1);
    if (send(s2, &msg, sizeof msg, 0) < 0) {
        perror("send");
        exit(1);
    }
    while (1) {
        struct timeval start, end;
        if (recv(s2, &msg, sizeof msg, 0) < 0) {
            perror("recv");
            exit(1);
        }
        if (!msg.loseflag) {
            printf("相手が空振りしました.あなたの勝ちです!\n");
            return 0;
        }
        printf("!!");
        gettimeofday(&start, NULL);
        fgets(buf, DATA_SIZE, stdin);
        gettimeofday(&end, NULL);
        double sec = (double)(end.tv_sec - start.tv_sec);
        double msec = (double)(end.tv_usec -start.tv_usec);
        double elapsed = sec + msec / 1000 / 1000;
        printf("%f\n", elapsed);
        if (elapsed > msg.time*1.1)
            break;
        msg.time = elapsed;
        sleep(rand()%10+1);
        
        if (send(s2, &msg, sizeof msg, 0) < 0) {
            perror("send");
            exit(1);
        }
    }
    msg.loseflag = 0;
    if (send(s2, &msg, sizeof msg, 0) < 0) {
            perror("send");
            exit(1);
    }
    printf("空振り. あなたの負けです!\n");
}