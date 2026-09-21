게임프로그래밍 3주차

이번 주 학습 내용

이번 주에는 기존 C 기초를 복습하면서 함수와 모듈화, 난수, 카드 셔플로 확장했다.

C 언어의 컴파일 단위

모듈화와 함수

getch()의 반환값

getch() - 48을 사용하는 이유

수식(Expression)과 할당문(Assignment Statement)

함수 프로토타입 확인 방법

rand(), srand(), seed

time()을 seed로 사용하는 이유

나머지 연산자를 이용한 난수 범위 제한

카드 자료구조와 shuffle

Git / GitHub 기본 개념

이력서·자기소개서 GitHub 업로드 과제

C 언어의 컴파일 단위

교수님이 강조한 핵심은 C 언어는 .c 소스 파일 단위로 컴파일한다는 것이다.

source1.c ─┐
           ├─ Compile → Object Files → Link → 실행 파일
source2.c ─┘

include : 헤더 파일과 함수 선언 정보

lib : 링크 과정에서 사용하는 라이브러리 관련 파일

여러 .c 파일을 하나의 프로그램으로 만들려면 각각 컴파일한 뒤 Link 과정에서 결합한다.

모듈화

프로그램 전체를 main() 하나에 몰아넣기보다 기능을 함수로 나눈다.

int menu_display(void);
void hamburger(void);
void spaghetti(void);
void press_any_key(void);

main()은 필요한 함수를 호출하는 중심 역할을 하도록 구성할 수 있다.

getch() - 48

getch()는 사용자가 누른 키의 코드 값을 반환한다.

ASCII에서 숫자 문자는 다음처럼 연속되어 있다.

'0' = 48
'1' = 49
'2' = 50
...
'9' = 57

따라서:

select = getch() - 48;

사용자가 '1'을 누르면 49 - 48 = 1이 되어 실제 숫자 1로 사용할 수 있다.

수식의 구성 요소

기본 형태:

variable = expression

수식의 구성 요소로 다음이 언급되었다.

Literal / Constant

Variable

Operator

Function

예:

a = 1;
a = b;
a = b + 1;
a = sum(1, 2) * 6;

오른쪽 Expression을 계산한 뒤 결과를 왼쪽 변수에 할당한다.

함수 프로토타입

새로운 함수를 만나면 먼저 **Prototype(함수 원형)**을 확인한다.

확인할 것:

함수 이름

함수가 하는 일

Parameter

Return Value

필요한 Header File

Random과 Seed

C에서 난수를 생성할 때 rand()를 사용하고, 난수 생성의 시작값인 seed를 설정할 때 srand()를 사용한다.

srand((unsigned int)time(NULL));

현재 시간은 계속 변하기 때문에 실행할 때마다 다른 seed를 사용하기 쉽다.

주사위처럼 1~6 범위가 필요하면:

rand() % 6 + 1

rand() % 6 → 0~5
+ 1        → 1~6

Shuffle

Shuffle은 이미 존재하는 값들의 순서를 섞는 작업이다.

52장의 카드 생성
→ shuffle
→ 섞인 카드 출력 또는 분배

03_card_shuffle.c는 교수님의 설명을 바탕으로 작성한 수업 내용 기반 재구성 예제다. 강의 화면의 원본 코드를 그대로 옮긴 것은 아니다.

카드 데이터

조커를 제외한 기본 트럼프 카드는 52장이다.

4개의 무늬 × 13개의 숫자 = 52장

카드를 프로그램에서 표현할 때 무늬와 숫자 같은 정보를 구조체로 묶을 수 있다. 게임 규칙에 따라 우선순위 정보도 추가할 수 있다.

Git / GitHub

수업 발표에서 다음 개념을 다뤘다.

Repository

Staging

Commit

Branch

Merge

Remote

Push

Revert / Reset

기본 흐름:

작업 → git add → git commit → git push → GitHub

Git은 변경 이력을 관리하는 분산 버전 관리 시스템이고, GitHub는 Git 저장소를 인터넷에 저장하고 공유할 수 있는 서비스다.

이번 주 파일

파일

내용

01_menu.c

getch()-48을 사용하는 메뉴 프로그램

02_random_dice.c

rand, srand, time, % 난수 실습

03_card_shuffle.c

카드 52장 생성 → shuffle → 출력

LECTURE_NOTES.md

강의 핵심 정리

ASSIGNMENT.md

이력서·자기소개서 과제 정리

핵심 요약

C는 .c 파일 단위로 컴파일한다.
함수를 이용해 프로그램을 모듈화한다.
getch()는 키의 코드값을 반환한다.
'1'의 코드값 49에서 48을 빼면 숫자 1이 된다.
rand()는 난수를 만들고 srand()는 seed를 설정한다.
time()을 seed에 이용하면 실행할 때마다 다른 난수 순서를 만들 수 있다.
카드는 구조체/배열로 만들고 shuffle하여 순서를 섞을 수 있다.
