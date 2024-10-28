#include <stdio.h>
#include <stdlib.h>

// #define DELAY_TIME 3.0 // 지연 시간 3초

void print_splash_screen_with_triangles() {
    // 출력할 텍스트 배열 (4줄)
    const char* lines[] = {
        "[마그라테아 ver 0.1]",
        "풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,",
        "사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,",
        "마그라테아에 오신걸 환영합니다."
    };

    int height = 5;  // 삼각형의 높이
    int num_lines = sizeof(lines) / sizeof(lines[0]);  // 출력할 텍스트 줄 수

    // 각 줄에 추가할 공백의 양 (1, 2, 3, 4 번째 줄)
    int extra_spaces[] = { 11, 5, 0, 11, 0 };  // 첫 번째 줄은 공백이 10, 그 후 점차 감소

    // 삼각형과 텍스트 출력
    for (int i = 0; i < height; i++) {
        // 왼쪽 삼각형 출력 (정삼각형)
        for (int j = 0; j <= i; j++) {
            printf("*");
        }

        // 텍스트 출력 (중간 공백 포함)
        if (i < num_lines) {
            printf("%*s %-*s ", 5 - (i + 1), "", 55, lines[i]);  // 공백을 포함한 가운데 텍스트 출력 (너비 조정)
        } else {
            printf("%*s", 73, "");  // 텍스트 없는 줄 공백으로 맞춤
        }

        // 오른쪽 삼각형 출력 (역삼각형) - 줄마다 다른 공백을 추가해 위치 조정
        printf("%*s", extra_spaces[i], "");  // 각 줄에 대해 별을 오른쪽으로 이동시키는 공백 추가
        for (int j = 0; j < height - i; j++) {
            printf("*");
        }

        printf("\n");
    }
}

// 대기 함수 (시간 지연 구현)
void delay() {
    volatile long long count; // volatile을 사용하여 최적화를 방지
    for (count = 0; count < 1000000000; count++) {
        // 빈 루프를 돌며 시간 지연
    }
}

int main() {
    char name[100];
    char date[11]; // yyyy-mm-dd 형식

    // 날짜 입력 받기
    printf("[현재 날짜를 \"yyyy-mm-dd\" 형식으로 입력하세요]: ");
    if (scanf("%10s", date) != 1) { // scanf_s 대신 scanf 사용
        fprintf(stderr, "날짜 입력 오류! 올바른 형식으로 입력하세요.\n");
        return 1; // 오류 발생 시 프로그램 종료
    }

    // 이름 입력 받기
    printf("[당신의 이름을 입력하세요]: ");
    if (scanf("%99s", name) != 1) { // scanf_s 대신 scanf 사용
        fprintf(stderr, "이름 입력 오류! 올바른 형식으로 입력하세요.\n");
        return 1; // 오류 발생 시 프로그램 종료
    }

    // 입력 정상 처리 메시지
    printf("**입력이 정상적으로 처리되었습니다.**\n");

    // 3초 대기
    delay();

    // 화면 지우기
    system("cls"); // UNIX 시스템에서 화면 지우기, Windows에서는 system("cls");

    // 스플래시 화면 출력
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**\n");

    print_splash_screen_with_triangles();

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**\n");

    printf("[사용자]: %s                                   [실행 시간]: %s\n", name, date);
    printf("==================================================================================\n");

    return 0;
}
