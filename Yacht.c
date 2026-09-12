#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE_COUNT 5
#define ROUND_COUNT 5

// 주사위 출력
void printDice(int dice[]) {
    printf("주사위: ");
    for (int i = 0; i < DICE_COUNT; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

// 주사위 굴리기
void rollDice(int dice[]) {
    for (int i = 0; i < DICE_COUNT; i++) {
        dice[i] = rand() % 6 + 1;
    }
}

// 족보 판정 및 점수 계산
int calculateScore(int dice[], char category[]) {
    int count[7] = {0};

    // 각 눈의 개수 계산
    for (int i = 0; i < DICE_COUNT; i++) {
        count[dice[i]]++;
    }

    // 1. 요트: 5개 모두 같은 눈
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 5) {
            sprintf(category, "요트");
            return 50;
        }
    }

    // 2. 풀하우스: 3개 + 2개
    int hasThree = 0;
    int hasTwo = 0;

    for (int i = 1; i <= 6; i++) {
        if (count[i] == 3)
            hasThree = 1;
        else if (count[i] == 2)
            hasTwo = 1;
    }

    if (hasThree && hasTwo) {
        sprintf(category, "풀하우스");
        return 25;
    }

    // 3. 스트레이트: 연속된 눈 4개 이상
    int consecutive = 0;
    int maxConsecutive = 0;

    for (int i = 1; i <= 6; i++) {
        if (count[i] > 0) {
            consecutive++;
            if (consecutive > maxConsecutive)
                maxConsecutive = consecutive;
        } else {
            consecutive = 0;
        }
    }

    if (maxConsecutive >= 4) {
        sprintf(category, "스트레이트");
        return 30;
    }

    // 4. 포카드: 같은 눈 4개
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 4) {
            sprintf(category, "포카드");
            return i * 4;
        }
    }

    // 5. 트리플: 같은 눈 3개
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 3) {
            sprintf(category, "트리플");
            return i * 3;
        }
    }

    // 6. 원페어: 같은 눈 2개
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 2) {
            sprintf(category, "원페어");
            return i * 2;
        }
    }

    // 7. 아무 족보도 없음
    sprintf(category, "없음");
    return 0;
}

int main() {
    int dice[DICE_COUNT];
    int totalScore = 0;

    // 랜덤 시드 설정
    srand((unsigned int)time(NULL));

    printf("=================================\n");
    printf("        주사위 게임 '요트'\n");
    printf("=================================\n\n");

    for (int round = 1; round <= ROUND_COUNT; round++) {
        char category[20];
        int score;

        printf("-------- %d판 --------\n", round);

        // 주사위 5개 굴리기
        rollDice(dice);

        // 주사위 출력
        printDice(dice);

        // 족보 판정 및 점수 계산
        score = calculateScore(dice, category);

        printf("족보: %s\n", category);
        printf("점수: %d점\n", score);

        // 누적 점수
        totalScore += score;

        printf("누적 점수: %d점\n\n", totalScore);
    }

    printf("=================================\n");
    printf("          게임 종료!\n");
    printf("        최종 점수: %d점\n", totalScore);
    printf("=================================\n");

    return 0;
}
