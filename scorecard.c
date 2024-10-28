#include <stdio.h>
#include <stdlib.h>

#define MAX_CANDIDATES 6
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int id; // 고유 ID
} Candidate;

void input_scores(Candidate candidates[], int scores[MAX_CANDIDATES][7], int judge_index) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("후보자: %s\n", candidates[i].name);
        int score;

        // 음악 소양 점수 입력
        do {
            printf("음악 소양 점수 (10~100): ");
            scanf("%d", &score);
        } while (score < 10 || score > 100);
        scores[i][judge_index] = score;

        // 여기서 다른 분야 점수도 입력받을 수 있음
    }
}

void calculate_totals(int scores[MAX_CANDIDATES][7]) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        int total = 0;
        for (int j = 0; j < 5; j++) { // 5개의 점수 합산
            total += scores[i][j];
        }
        scores[i][6] = total; // 총점 저장
    }
}

void display_results(Candidate candidates[], int scores[MAX_CANDIDATES][7]) {
    printf("입력을 모두 완료했습니다.\n");
    printf("입력하신 내용을 검토하세요!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s: %d\n", candidates[i].name, scores[i][6]);
    }
}

int main() {
    Candidate candidates[MAX_CANDIDATES] = {
        {"박지연", 123456},
        {"Ethan Smith", 234567},
        {"Helena Silva", 345678},
        {"Liam Wilson", 456789},
        {"Emma Brown", 567890},
        {"Oliver Jones", 678901}
    };

    int scores[MAX_CANDIDATES][7] = {0}; // 후보자 점수 저장 배열
    int judge_index = 0;

    char judge_name[MAX_NAME_LENGTH];
    char specialty[MAX_NAME_LENGTH];

    printf("심사자 이름: ");
    scanf("%s", judge_name);
    printf("전문 분야: ");
    scanf("%s", specialty);

    input_scores(candidates, scores, judge_index);
    calculate_totals(scores);
    display_results(candidates, scores);

    // 제출 여부 확인
    char submit;
    printf("제출하시겠습니까? (Y/N): ");
    scanf(" %c", &submit);
    
    if (submit == 'Y' || submit == 'y') {
        printf("***최종 제출을 완료했습니다.***\n");
    } else {
        // 점수 수정 기능
        while (1) {
            int id_to_modify;
            printf("수정할 후보자의 고유 ID 입력 (종료하려면 -1 입력): ");
            scanf("%d", &id_to_modify);
            if (id_to_modify == -1) break;

            for (int i = 0; i < MAX_CANDIDATES; i++) {
                if (candidates[i].id == id_to_modify) {
                    int new_score;
                    printf("%s의 새 음악 소양 점수 (10~100): ", candidates[i].name);
                    scanf("%d", &new_score);
                    if (new_score >= 10 && new_score <= 100) {
                        scores[i][0] = new_score; // 음악 소양 점수 수정
                        scores[i][6] = 0; // 총점 초기화
                        calculate_totals(scores); // 총점 재계산
                    } else {
                        printf("잘못된 점수입니다.\n");
                    }
                    break;
                }
            }
        }
    }

    // 최종 후보 선발
    printf("=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸축하합니다!  #\n");
    printf("#######################################\n");

    // 점수에 따라 후보자 정렬 (총점 기준)
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        for (int j = i + 1; j < MAX_CANDIDATES; j++) {
            if (scores[i][6] < scores[j][6]) {
                // 점수 교환
                int temp_score[7];
                for (int k = 0; k < 7; k++) {
                    temp_score[k] = scores[i][k];
                    scores[i][k] = scores[j][k];
                    scores[j][k] = temp_score[k];
                }

                // 후보자 이름 교환
                Candidate temp_candidate = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp_candidate;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    return 0;
}
