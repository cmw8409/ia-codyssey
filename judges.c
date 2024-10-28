#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256
#define MAX_JUDGES 5

typedef struct {
    char name[MAX_LENGTH];
    char gender[MAX_LENGTH];
    char affiliation[MAX_LENGTH];
    char title[MAX_LENGTH];
    char expertise[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];
} Judge;

void inputJudgeData(Judge *judge, int index) {
    char buffer[MAX_LENGTH];
    int valid = 0;

    while (!valid) {
        printf("*심사자 %d: ", index + 1);
        fgets(buffer, sizeof(buffer), stdin);

        // 개행 문자 제거
        for (int i = 0; i < MAX_LENGTH; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }

        // JSON 형식 파싱
        if (sscanf(buffer, "이름:%[^,],성별:%[^,],소속:%[^,],직함:%[^,],전문분야:%[^,],메일:%[^,],전화:%[^\n]",
                   judge->name, judge->gender, judge->affiliation, judge->title, 
                   judge->expertise, judge->email, judge->phone) == 7) {
            valid = 1;
        } else {
            printf("입력 항목이 정확하지 않습니다. 다시 입력해주세요.\n");
        }
    }
}

void printJudges(Judge judges[], int count) {
    printf("####################################\n");
    printf("#       심사자 풀 데이터 출력       #\n");
    printf("####################################\n");
    
    for (int i = 0; i < count; i++) {
        printf("[심사자 %d]\n", i + 1);
        printf("이름:%s\n", judges[i].name);
        printf("성별:%s\n", judges[i].gender);
        printf("소속:%s\n", judges[i].affiliation);
        printf("직함:%s\n", judges[i].title);
        printf("전문분야:%s\n", judges[i].expertise);
        printf("메일:%s\n", judges[i].email);
        printf("전화:%s\n", judges[i].phone);
        printf("-----------------------------------\n");
    }
}

int main() {
    Judge judges[MAX_JUDGES];
    char project[MAX_LENGTH];
    int judgeCount;

    printf("####################################\n");
    printf("#       심사자 풀 데이터 입력       #\n");
    printf("####################################\n");
    
    printf("> 참여 프로젝트: ");
    fgets(project, sizeof(project), stdin);

    // 개행 문자 제거
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (project[i] == '\n') {
            project[i] = '\0';
            break;
        }
    }

    printf("> 심사 풀 인원(최대 %d명): ", MAX_JUDGES);
    scanf("%d", &judgeCount);
    getchar(); // 개행 문자 제거

    if (judgeCount > MAX_JUDGES) {
        judgeCount = MAX_JUDGES;
        printf("최대 인원 수로 설정되었습니다: %d\n", MAX_JUDGES);
    }

    // 선발 멤버 수를 심사 풀 인원 수에서 -1로 설정
    int selectedMembers = judgeCount - 1;
    if (selectedMembers < 0) selectedMembers = 0; // 음수 방지

    printf("> 선발 멤버 수: %d\n", selectedMembers);
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사자 정보 입력을 시작합니다.\n", judgeCount);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < judgeCount; i++) {
        inputJudgeData(&judges[i], i);
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사자 풀 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    
    printf("“심사자 풀을 확인할까요?” Y(확인)나 N(종료) 문자(대문자)를 입력해주세요: ");
    
    char choice;
    while (1) {
        choice = getchar();
        while (getchar() != '\n'); // 입력 버퍼 비우기

        if (choice == 'Y') {
            printJudges(judges, judgeCount);
            printf("결과를 확인했습니다. 프로그램을 종료하려면 Enter를 누르세요...\n");
            getchar(); // Enter 입력 대기
            break;
        } else if (choice == 'N') {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 입력입니다. Y 또는 N을 입력해주세요: ");
        }
    }

    return 0;
}
