#include <stdio.h>
#include <stdlib.h>

#define MAX_CANDIDATES 6
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int id; // ���� ID
} Candidate;

void input_scores(Candidate candidates[], int scores[MAX_CANDIDATES][7], int judge_index) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("�ĺ���: %s\n", candidates[i].name);
        int score;

        // ���� �Ҿ� ���� �Է�
        do {
            printf("���� �Ҿ� ���� (10~100): ");
            scanf("%d", &score);
        } while (score < 10 || score > 100);
        scores[i][judge_index] = score;

        // ���⼭ �ٸ� �о� ������ �Է¹��� �� ����
    }
}

void calculate_totals(int scores[MAX_CANDIDATES][7]) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        int total = 0;
        for (int j = 0; j < 5; j++) { // 5���� ���� �ջ�
            total += scores[i][j];
        }
        scores[i][6] = total; // ���� ����
    }
}

void display_results(Candidate candidates[], int scores[MAX_CANDIDATES][7]) {
    printf("�Է��� ��� �Ϸ��߽��ϴ�.\n");
    printf("�Է��Ͻ� ������ �����ϼ���!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s: %d\n", candidates[i].name, scores[i][6]);
    }
}

int main() {
    Candidate candidates[MAX_CANDIDATES] = {
        {"������", 123456},
        {"Ethan Smith", 234567},
        {"Helena Silva", 345678},
        {"Liam Wilson", 456789},
        {"Emma Brown", 567890},
        {"Oliver Jones", 678901}
    };

    int scores[MAX_CANDIDATES][7] = {0}; // �ĺ��� ���� ���� �迭
    int judge_index = 0;

    char judge_name[MAX_NAME_LENGTH];
    char specialty[MAX_NAME_LENGTH];

    printf("�ɻ��� �̸�: ");
    scanf("%s", judge_name);
    printf("���� �о�: ");
    scanf("%s", specialty);

    input_scores(candidates, scores, judge_index);
    calculate_totals(scores);
    display_results(candidates, scores);

    // ���� ���� Ȯ��
    char submit;
    printf("�����Ͻðڽ��ϱ�? (Y/N): ");
    scanf(" %c", &submit);
    
    if (submit == 'Y' || submit == 'y') {
        printf("***���� ������ �Ϸ��߽��ϴ�.***\n");
    } else {
        // ���� ���� ���
        while (1) {
            int id_to_modify;
            printf("������ �ĺ����� ���� ID �Է� (�����Ϸ��� -1 �Է�): ");
            scanf("%d", &id_to_modify);
            if (id_to_modify == -1) break;

            for (int i = 0; i < MAX_CANDIDATES; i++) {
                if (candidates[i].id == id_to_modify) {
                    int new_score;
                    printf("%s�� �� ���� �Ҿ� ���� (10~100): ", candidates[i].name);
                    scanf("%d", &new_score);
                    if (new_score >= 10 && new_score <= 100) {
                        scores[i][0] = new_score; // ���� �Ҿ� ���� ����
                        scores[i][6] = 0; // ���� �ʱ�ȭ
                        calculate_totals(scores); // ���� ����
                    } else {
                        printf("�߸��� �����Դϴ�.\n");
                    }
                    break;
                }
            }
        }
    }

    // ���� �ĺ� ����
    printf("=======================================\n");
    printf("�ĺ� ���� ��� ���� �� ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# �и��������� ����� �� �������մϴ�!  #\n");
    printf("#######################################\n");

    // ������ ���� �ĺ��� ���� (���� ����)
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        for (int j = i + 1; j < MAX_CANDIDATES; j++) {
            if (scores[i][6] < scores[j][6]) {
                // ���� ��ȯ
                int temp_score[7];
                for (int k = 0; k < 7; k++) {
                    temp_score[k] = scores[i][k];
                    scores[i][k] = scores[j][k];
                    scores[j][k] = temp_score[k];
                }

                // �ĺ��� �̸� ��ȯ
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
