#include<iostream>
#include<conio.h>  // _kbhit(), _getch() 함수를 사용하기 위함
#include<windows.h> // system("CLS"), Sleep() 함수를 사용하기 위함

using namespace std;

bool gameOver; // 게임 종료 여부를 저장
const int height = 20; // 게임 높이
const int width = 20;  // 게임 너비

int x, y, fruitX, fruitY, score; // 뱀의 머리 좌표(x, y), 과일 좌표(fruitX, fruitY), 점수(score)

int tailX[100], tailY[100], nTail; // 뱀의 꼬리 좌표 배열과 길이(nTail)

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT }; // 이동 방향을 나타냄
eDirection dir; // 현재 이동 방향을 저장하는 변수

// 게임 초기 설정 함수
void Setup() {
    gameOver = false; // 게임 시작 상태
    dir = STOP; // 초기에는 이동하지 않음
    x = width / 2; // 뱀의 시작 위치 (가운데)
    y = height / 2;
    fruitX = rand() % width; // 랜덤한 위치에 과일 생성
    fruitY = rand() % height;
}

// 게임 화면을 출력하는 함수
void Draw() {
    system("CLS"); // 화면을 지워서 새롭게 그릴 준비

    // 상단 벽 출력
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    // 보드 내부 출력
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) { 
                cout << "#"; // 좌우 벽
            } 
            else if (i == y && j == x) { 
                cout << "O"; // 뱀의 머리
            } 
            else if (i == fruitY && j == fruitX) { 
                cout << "F"; // 과일
            } 
            else {
                bool print = false;

                // 뱀의 꼬리 부분 출력
                for (int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << "o"; // 뱀의 꼬리
                        print = true;
                        break;
                    }
                }
                if (!print) { 
                    cout << " "; // 빈 공간 출력
                }
            }
        }
        cout << endl;
    }

    // 하단 벽 출력
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    // 점수 출력
    cout << "\nScore: " << score << endl;
}

// 키보드 입력을 처리하는 함수
void Input() {
    if (_kbhit()) { // 키보드 입력이 있는 경우
        switch (_getch()) { // 입력된 키를 가져와 처리
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
        }
    }
}

// 게임 로직을 처리하는 함수
void Logic() {
    // 꼬리의 이동을 처리하기 위해 이전 좌표 저장
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    // 꼬리가 따라가도록 좌표 갱신
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 방향에 따라 뱀 이동
    switch (dir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }

    // 벽 충돌 시 게임 종료
    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = true;
    }

    // 과일을 먹었을 때 처리
    if (x == fruitX && y == fruitY) {
        score += 10; // 점수 증가
        fruitX = rand() % width; // 새로운 과일 생성
        fruitY = rand() % height;
        nTail++; // 꼬리 길이 증가
    }

    // 자기 꼬리와 충돌하면 게임 종료
    for (int i = 0; i < nTail; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            gameOver = true;
        }
    }
}

// 메인 함수 (게임 실행)
int main() {
    Setup(); // 초기 설정

    while (!gameOver) { // 게임 종료 전까지 반복 실행
        Draw();   // 화면 갱신
        Input();  // 키 입력 처리
        Logic();  // 게임 로직 처리
        Sleep(60); // 게임 속도 조절 (60ms 딜레이)
    }

    return 0;
}
