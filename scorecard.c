#include <stdio.h>

#define MAX_CANDIDATES 6
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int id; // 6자리 고유 ID
    int scores[5]; // 음악 소양, 댄스, 보컬, 비주얼, 전달력 점수
    int totalScore; // 총점
} Candidate;

// 후보자 배열 초기화
Candidate candidates[MAX_CANDIDATES] = {
    {"박지연", 123456},
    {"Ethan Smith", 234567},
    {"Helena Silva", 345678},
    {"Liam Wilson", 456789},
    {"Olivia Brown", 567890},
    {"Noah Johnson", 678901}
};

void inputScores(const char *judgeName, const char *specialization) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("후보자: %s\n", candidates[i].name);
        for (int j = 0; j < 5; j++) {
            int score;
            do {
                switch (j) {
                    case 0:
                        printf("%s 소양 점수 (10~100): ", specialization); // 음악 소양 점수
                        break;
                    case 1:
                        printf("댄스 점수 (10~100): ");
                        break;
                    case 2:
                        printf("보컬 점수 (10~100): ");
                        break;
                    case 3:
                        printf("비주얼 점수 (10~100): ");
                        break;
                    case 4:
                        printf("전달력 점수 (10~100): ");
                        break;
                }
                scanf("%d", &score);
                if (score < 10 || score > 100) {
                    printf("잘못된 점수입니다. 10에서 100 사이의 점수를 입력하세요.\n");
                }
            } while (score < 10 || score > 100);
            candidates[i].scores[j] = score; // 각 점수 입력
        }
    }
}

void printScores() {
    printf("\n입력을 모두 완료했습니다.\n");
    printf("입력하신 내용을 검토하세요!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s: ", candidates[i].name);
        for (int j = 0; j < 5; j++) {
            printf("%d ", candidates[i].scores[j]);
        }
        printf("총점: %d\n", candidates[i].totalScore);
    }
}

char confirmSubmission() {
    char confirm;
    printf("제출하시겠습니까? (Y/N): ");
    scanf(" %c", &confirm);
    return confirm;
}

void modifyScore() {
    int id, newScores[5];
    printf("수정할 후보자의 고유 ID 입력: ");
    scanf("%d", &id);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (candidates[i].id == id) {
            printf("현재 점수: ");
            for (int j = 0; j < 5; j++) {
                printf("%d ", candidates[i].scores[j]);
            }
            printf("\n새 점수를 입력하세요 (10~100): \n");
            for (int j = 0; j < 5; j++) {
                do {
                    switch (j) {
                        case 0:
                            printf("소양 점수: ");
                            break;
                        case 1:
                            printf("댄스 점수: ");
                            break;
                        case 2:
                            printf("보컬 점수: ");
                            break;
                        case 3:
                            printf("비주얼 점수: ");
                            break;
                        case 4:
                            printf("전달력 점수: ");
                            break;
                    }
                    scanf("%d", &newScores[j]);
                    if (newScores[j] < 10 || newScores[j] > 100) {
                        printf("잘못된 점수입니다. 10에서 100 사이의 점수를 입력하세요.\n");
                    }
                } while (newScores[j] < 10 || newScores[j] > 100);
            }
            for (int j = 0; j < 5; j++) {
                candidates[i].scores[j] = newScores[j];
            }
            printf("점수가 수정되었습니다.\n");
            return;
        }
    }
    printf("해당 ID를 가진 후보자가 없습니다.\n");
}

void calculateTotalScores() {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        candidates[i].totalScore = 0;
        for (int j = 0; j < 5; j++) {
            candidates[i].totalScore += candidates[i].scores[j]; // 총점 계산
        }
    }
}

void selectFinalMembers() {
    printf("\n=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸축하합니다!  #\n");
    printf("#######################################\n");

    // 간단한 정렬을 통해 점수 순으로 정렬
    for (int i = 0; i < MAX_CANDIDATES - 1; i++) {
        for (int j = 0; j < MAX_CANDIDATES - i - 1; j++) {
            if (candidates[j].totalScore < candidates[j + 1].totalScore) {
                Candidate temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 4; i++) { // 상위 4명 출력
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
}

int main() {
    char judgeName[MAX_NAME_LENGTH];
    char specialization[MAX_NAME_LENGTH];

    printf("####################################\n");
    printf("#       오디션 심사 결과 입력       #\n");
    printf("####################################\n");

    // 심사자 이름과 전문 분야 입력
    printf("> 심사자 이름: ");
    scanf("%s", judgeName);
    printf("> 전문 분야: ");
    scanf("%s", specialization);

    // 점수 입력
    inputScores(judgeName, specialization);

    // 총점 계산
    calculateTotalScores();

    // 점수 출력
    printScores();

    // 제출 확인
    char submission = confirmSubmission();
    if (submission == 'Y' || submission == 'y') {
        printf("***최종 제출을 완료했습니다.***\n");
    } else if (submission == 'N' || submission == 'n') {
        while (1) {
            modifyScore();
            printf("수정을 계속하시겠습니까? (Y/N): ");
            char continueModifying;
            scanf(" %c", &continueModifying);
            if (continueModifying == 'N' || continueModifying == 'n') {
                break;
            }
        }
    }

    // 최종 멤버 선발
    selectFinalMembers();

    return 0;
}
