게임프로그래밍 1주차 — 2026-09-04

1. 오늘 수업 목표

오늘은 본격적인 게임 제작에 들어가기 전에 C 언어 개발 환경과
콘솔 기반 게임에서 필요한 기초 기능을 확인했다.

핵심은 다음과 같다.

VSCode에서 C 프로그램을 작성하고 컴파일할 수 있는 환경 구성

GCC 설치 및 동작 확인

C 파일의 확장자와 VSCode의 자동완성 기능 확인

Hello World 프로그램 실행

Windows 콘솔에서 커서 위치를 좌표로 이동

원하는 좌표에 문자열 또는 숫자 출력

system("cls")로 콘솔 화면 지우기

2. VSCode와 C 컴파일

VSCode는 기본적으로 텍스트 에디터이며 C 컴파일러 자체를 포함하지 않는다.
따라서 GCC 같은 C 컴파일러를 별도로 설치한 뒤 VSCode에서 사용할 수 있도록 해야 한다.

이번 실습 환경에서는 Windows에서 MSYS2를 이용해 GCC를 설치했다.

GCC 확인

gcc --version

정상적으로 버전 정보가 출력되면 GCC가 설치되어 있고 PATH에서도 인식되는 상태이다.

C 파일 컴파일

gcc hello.c -o hello.exe

실행

PowerShell:

.\hello.exe

3. VSCode에서 C 파일 만들기

C 소스 파일은 확장자를 반드시 .c로 지정한다.

예:

hello.c

VSCode는 파일 확장자를 기준으로 언어 기능, 자동완성, 구문 강조 등을 결정하기 때문에
확장자를 정확하게 작성하는 것이 중요하다.

4. C Skeleton 스니펫

VSCode의 User Snippet 기능을 이용하면 반복해서 작성하는 C 프로그램의 기본 뼈대를
단축어로 자동 입력할 수 있다.

이 폴더의 c.code-snippets 파일에는 다음 스니펫이 들어 있다.

c-main : 기본 main() 함수

c-main-args : argc, argv를 사용하는 main() 함수

스니펫 입력 후 Tab, Enter, 또는 자동완성 선택으로 코드를 빠르게 작성할 수 있다.

5. 함수 프로토타입

교수님은 함수를 사용할 때 다음 정보를 확인하는 습관이 중요하다고 설명했다.

함수가 무슨 일을 하는가

어떤 매개변수(parameter)를 받는가

호출할 때 어떤 인수(argument)를 전달해야 하는가

어떤 값을 반환(return)하는가

어느 헤더 파일에 선언되어 있는가

C에서는 일반적으로 함수를 사용하기 전에 필요한 헤더 파일을 #include해야 한다.

6. include와 lib

C 컴파일 환경에서 자주 확인하게 되는 디렉터리는 다음 두 가지다.

include : 헤더 파일과 함수 선언 정보

lib : 링크할 때 사용하는 라이브러리 관련 파일

프로그램이 실행 파일이 되기까지는 소스 코드가 컴파일되고,
필요한 라이브러리가 링크되는 과정이 필요하다.

7. 콘솔 좌표와 커서 이동

텍스트 모드 게임에서는 그래픽 화면 대신 콘솔의 특정 위치에 문자를 출력한다.

콘솔의 좌측 상단을 (0, 0)으로 보고,
x, y 좌표를 이용해 커서를 이동시킨 뒤 printf()로 내용을 출력할 수 있다.

Windows에서는 windows.h의 다음 요소를 이용할 수 있다.

COORD

GetStdHandle()

SetConsoleCursorPosition()

이 수업 내용을 바탕으로 gotoxy() 함수를 만들어 사용했다.

gotoxy() 자체는 C 표준 함수가 아니라 Windows 콘솔 API를 이용해 만든 사용자 함수이다.

8. 지정 좌표 출력

gotoxy(x, y)로 원하는 위치로 이동한 뒤 printf()를 사용하면
콘솔의 특정 좌표에 문자열이나 숫자를 출력할 수 있다.

예를 들어 구구단을 일정한 x 좌표에 두고,
y 좌표만 증가시키면서 세로 방향으로 출력할 수 있다.

관련 예제:

02_gotoxy.c

03_gugudan.c

9. 화면 지우기

Windows 명령 프롬프트에서 cls는 화면을 지우는 명령이다.

C에서는 system() 함수를 이용해 명령 프롬프트 명령을 실행할 수 있다.

system("cls");

system()을 사용하려면 다음 헤더가 필요하다.

#include <stdlib.h>

관련 예제:

04_clear_screen.c

10. CLI

CLI는 Command Line Interface의 약자이다.

명령어를 직접 입력해 컴퓨터와 상호작용하는 방식이며,
Windows의 Command Prompt와 PowerShell, Linux 터미널 등이 대표적이다.

수업에서는 콘솔 기반 텍스트 게임을 만들기 때문에
CLI 환경과 콘솔 입출력에 대한 이해가 중요하다.

11. 오늘 작성한 파일

파일

내용

01_hello.c

기본 C 프로그램과 Hello World 출력

02_gotoxy.c

Windows 콘솔 커서 좌표 이동

03_gugudan.c

지정 좌표에서 구구단 출력

04_clear_screen.c

system("cls")를 이용한 화면 지우기

c.code-snippets

VSCode C Skeleton 스니펫

SETUP.md

MSYS2/GCC 설치 및 컴파일 환경 정리

12. 컴파일 예시

gcc 01_hello.c -o 01_hello.exe
gcc 02_gotoxy.c -o 02_gotoxy.exe
gcc 03_gugudan.c -o 03_gugudan.exe
gcc 04_clear_screen.c -o 04_clear_screen.exe

PowerShell 실행 예:

.\01_hello.exe

13. 교수님이 강조한 내용

머릿속으로 아는 것과 다른 사람에게 설명할 수 있는 것은 다르다.

개발 환경 설정 과정도 직접 설명할 수 있을 정도로 이해해야 한다.

수업마다 결과물(output)을 만들어 포트폴리오에 남기는 것이 중요하다.

수업에서 만든 소스와 레포트는 GitHub에 날짜별로 정리한다.

기존 게임 소스를 그대로 제출하는 것이 아니라 기능을 추가하고 개선한 내용을 보여줘야 한다.

AI를 사용할 수 있지만 결과를 이해하고 판단하는 능력이 필요하다.

14. 수업 운영 관련 메모

교수님 설명에서 다음 내용이 언급되었다.

C 기초와 텍스트 모드 게임을 먼저 진행

이후 웹 게임, Unity/Unreal 입문 및 프로젝트 진행

프로젝트 결과물을 GitHub와 발표를 통해 평가

GitHub 정리가 평가에 포함됨

결석 2회 또는 지각 4회 시 A그룹에서 제외될 수 있음

상대평가에서 A그룹 최대 40%, B그룹까지 누적 최대 80%라고 안내

세부 배점과 일정은 추후 강의자료 및 교수님 공지를 기준으로 다시 확인한다.
