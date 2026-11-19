#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define box_length 15
#define box_height 15

#define TARGET_HEIGHT 10
#define MAX_TRIES 15

#define ACTION_RESTART -1
#define ACTION_EXIT    -2

#define LEFT_PANEL_WIDTH 18
#define RIGHT_PANEL_WIDTH 20
#define PANEL_HEIGHT 17
#define PANEL_GAP 2

void intro_game(void);
void select_difficulty(void);
int game_control(void);

void update_layout(void);
void gotoxy(int x, int y);

void draw_game_screen(void);
void draw_panel_box(int x, int y, int width, int height);
void draw_controls(void);
void draw_status(int count, int show_plus_one);
void draw_rectangle(int c, int r);
void draw_target_line(void);

int left_right_move(void);
void move_down(int x);
int max_block(void);
void reset_game(void);

void print_block(void);
void print_spaces(int count);
void print_target_marks(int count);

void play_land_sound(void);
void play_height_sound(void);
void play_clear_sound(void);
void play_game_over_sound(void);

void end_animation(int clear_success, int count);
int wait_end_choice(void);

int block_stack[box_length * 2 + 1] = {0};

int origin_x = 0;
int origin_y = 0;

int cell_width = 2;
int board_width = 0;
int layout_width = 0;
int layout_height = 21;

int left_x = 1;
int board_x = 0;
int right_x = 0;

int panel_y = 4;
int board_y = 4;

int move_speed = 50;
const char *difficulty_name = "NORMAL";



int main(void)
{
    int action;

    SetConsoleOutputCP(CP_UTF8);

    intro_game();
    select_difficulty();

    while(1)
    {
        action = game_control();

        if(action == ACTION_EXIT)
            break;
    }

    system("cls");
    printf("게임을 종료합니다.\n");

    return 0;
}


void intro_game(void)
{
    system("cls");
    update_layout();

    gotoxy(board_x + 4, 2);
    printf("블록 쌓기");

    gotoxy(board_x + 2, 7);
    printf("블록을 쌓아 목표 높이 10에 도전하세요.");

    gotoxy(board_x + 2, 9);
    printf("총 15번의 기회가 주어집니다.");

    gotoxy(board_x + 2, 12);
    printf("아무 키나 누르면 시작합니다.");

    getch();
}


void select_difficulty(void)
{
    int key;

    while(1)
    {
        system("cls");
        update_layout();

        gotoxy(board_x + 4, 3);
		printf("난이도를 선택하세요");

		gotoxy(board_x + 4, 7);
		printf("1. 쉬움");

		gotoxy(board_x + 4, 9);
		printf("2. 보통");

		gotoxy(board_x + 4, 11);
		printf("3. 어려움");

		gotoxy(board_x + 4, 14);
		printf("숫자 키를 눌러 선택하세요");

        key = getch();

        if(key == '1')
        {
            move_speed = 70;
            difficulty_name = "쉬움";
            break;
        }
        else if(key == '2')
        {
            move_speed = 50;
            difficulty_name = "보통";
            break;
        }
        else if(key == '3')
        {
            move_speed = 30;
            difficulty_name = "어려움";
            break;
        }
    }
}


int game_control(void)
{
    int x;
    int count = 0;
    int before_height;
    int after_height;

    reset_game();

    system("cls");
    update_layout();

    draw_game_screen();
    draw_status(count, 0);

    while(count < MAX_TRIES)
    {
        x = left_right_move();

        if(x == ACTION_RESTART)
            return ACTION_RESTART;

        if(x == ACTION_EXIT)
            return ACTION_EXIT;

        before_height = max_block();

        block_stack[x] += 1;
        move_down(x);

        while(kbhit())
            getch();

        count++;

        after_height = max_block();

        if(after_height > before_height)
        {
            draw_status(count, 1);
            play_height_sound();
            Sleep(250);
            draw_status(count, 0);
        }
        else
        {
            play_land_sound();
            draw_status(count, 0);
        }

        if(after_height >= TARGET_HEIGHT)
        {
            play_clear_sound();
            end_animation(1, count);
            return wait_end_choice();
        }
    }

    play_game_over_sound();
    end_animation(0, count);

    return wait_end_choice();
}


void update_layout(void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    int window_width;
    int window_height;
    int available_board_width;

    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &info
    );

    window_width =
        info.srWindow.Right -
        info.srWindow.Left + 1;

    window_height =
        info.srWindow.Bottom -
        info.srWindow.Top + 1;

    available_board_width =
        window_width
        - LEFT_PANEL_WIDTH
        - RIGHT_PANEL_WIDTH
        - (PANEL_GAP * 2)
        - 4;

    cell_width = available_board_width / box_length;

    if(cell_width < 1)
        cell_width = 1;

    if(cell_width > 4)
        cell_width = 4;

    board_width = box_length * cell_width + 2;

    layout_width =
        LEFT_PANEL_WIDTH
        + PANEL_GAP
        + board_width
        + PANEL_GAP
        + RIGHT_PANEL_WIDTH;

    left_x = 1;

    board_x =
        left_x
        + LEFT_PANEL_WIDTH
        + PANEL_GAP;

    right_x =
        board_x
        + board_width
        + PANEL_GAP;

    if(window_width > layout_width)
    {
        origin_x =
            info.srWindow.Left
            + (window_width - layout_width) / 2;
    }
    else
    {
        origin_x = info.srWindow.Left;
    }

    if(window_height > layout_height)
    {
        origin_y =
            info.srWindow.Top
            + (window_height - layout_height) / 2;
    }
    else
    {
        origin_y = info.srWindow.Top;
    }
}


void gotoxy(int x, int y)
{
    COORD Pos =
    {
        (SHORT)(origin_x + x - 1),
        (SHORT)(origin_y + y - 1)
    };

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        Pos
    );
}


void draw_game_screen(void)
{
    gotoxy(board_x + (board_width / 2) - 4, 2);
    printf("블록 쌓기");

    draw_panel_box(
        left_x,
        panel_y,
        LEFT_PANEL_WIDTH,
        PANEL_HEIGHT
    );

    draw_rectangle(
        box_length,
        box_height
    );

    draw_panel_box(
        right_x,
        panel_y,
        RIGHT_PANEL_WIDTH,
        PANEL_HEIGHT
    );

    draw_controls();
    draw_target_line();
}


void draw_panel_box(int x, int y, int width, int height)
{
    int i;

    gotoxy(x, y);
    printf("┌");

    for(i = 0; i < width - 2; i++)
        printf("─");

    printf("┐");

    for(i = 1; i < height - 1; i++)
    {
        gotoxy(x, y + i);
        printf("│");

        print_spaces(width - 2);

        printf("│");
    }

    gotoxy(x, y + height - 1);
    printf("└");

    for(i = 0; i < width - 2; i++)
        printf("─");

    printf("┘");
}


void draw_controls(void)
{
    gotoxy(left_x + 6, panel_y + 2);
    printf("조작법");

    gotoxy(left_x + 2, panel_y + 4);
    printf("블록 떨어뜨리기");

    gotoxy(left_x + 6, panel_y + 5);
    printf("SPACE");

    gotoxy(left_x + 2, panel_y + 8);
    printf("다시 시작");

    gotoxy(left_x + 8, panel_y + 9);
    printf("R");

    gotoxy(left_x + 2, panel_y + 12);
    printf("게임 종료");

    gotoxy(left_x + 7, panel_y + 13);
    printf("ESC");
}


void draw_status(int count, int show_plus_one)
{
    int height = max_block();
    int chance = MAX_TRIES - count;

    gotoxy(right_x + 7, panel_y + 2);
    printf("상태");

    gotoxy(right_x + 2, panel_y + 4);
    printf("성공한 블록");

    gotoxy(right_x + 3, panel_y + 5);

    if(show_plus_one)
        printf("%2d / %2d  +1 ", height, TARGET_HEIGHT);
    else
        printf("%2d / %2d     ", height, TARGET_HEIGHT);

    gotoxy(right_x + 2, panel_y + 8);
    printf("남은 기회");

    gotoxy(right_x + 7, panel_y + 9);
    printf("%2d ", chance);

    gotoxy(right_x + 2, panel_y + 12);
    printf("난이도");

    gotoxy(right_x + 4, panel_y + 13);
    printf("%-8s", difficulty_name);

    gotoxy(right_x + 2, panel_y + 15);
    printf("목표 높이 : %2d", TARGET_HEIGHT);
}


void draw_rectangle(int c, int r)
{
    int i;

    gotoxy(board_x, board_y);

    printf("┌");

    for(i = 0; i < c * cell_width; i++)
        printf("─");

    printf("┐");

    for(i = 0; i < r; i++)
    {
        gotoxy(board_x, board_y + i + 1);

        printf("│");

        print_spaces(c * cell_width);

        printf("│");
    }

    gotoxy(board_x, board_y + r + 1);

    printf("└");

    for(i = 0; i < c * cell_width; i++)
        printf("─");

    printf("┘");
}


void draw_target_line(void)
{
    int x;
    int column;
    int target_y;

    target_y =
        board_y
        + 1
        + (box_height - TARGET_HEIGHT);

    for(column = 0; column < box_length; column++)
    {
        x = column * 2 + 1;

        gotoxy(
            board_x + 1 + column * cell_width,
            target_y
        );

        if(block_stack[x] >= TARGET_HEIGHT)
            print_block();
        else
            print_target_marks(cell_width);
    }
}


int left_right_move(void)
{
    int column = 0;
    int direction = 1;
    int key;
    int x;
    int screen_x;

    while(1)
    {
        x = column * 2 + 1;

        screen_x =
            board_x
            + 1
            + column * cell_width;

        gotoxy(screen_x, board_y + 1);

        print_block();

        Sleep(move_speed);

        gotoxy(screen_x, board_y + 1);

        print_spaces(cell_width);

        if(kbhit())
        {
            key = getch();

            if(key == ' ')
                return x;

            if(key == 'r' || key == 'R')
                return ACTION_RESTART;

            if(key == 27)
                return ACTION_EXIT;

            if(key == 0 || key == 0xE0)
                getch();
        }

        column += direction;

        if(column >= box_length - 1)
        {
            column = box_length - 1;
            direction = -1;
        }
        else if(column <= 0)
        {
            column = 0;
            direction = 1;
        }
    }
}


void move_down(int x)
{
    int y;
    int column;
    int screen_x;
    int final_y;
    int target_y;

    column = (x - 1) / 2;

    screen_x =
        board_x
        + 1
        + column * cell_width;

    final_y =
        board_y
        + box_height
        + 1
        - block_stack[x];

    target_y =
        board_y
        + 1
        + (box_height - TARGET_HEIGHT);

    for(y = board_y + 1; y < final_y; y++)
    {
        gotoxy(screen_x, y);

        print_block();

        Sleep(20);

        gotoxy(screen_x, y);

        if(y == target_y && block_stack[x] < TARGET_HEIGHT)
            print_target_marks(cell_width);
        else
            print_spaces(cell_width);

        Sleep(10);
    }

    gotoxy(screen_x, final_y);
    print_block();
}


int max_block(void)
{
    int x;
    int max = 0;

    for(x = 1; x < box_length * 2; x += 2)
    {
        if(max < block_stack[x])
            max = block_stack[x];
    }

    return max;
}


void reset_game(void)
{
    int i;

    for(i = 0; i < box_length * 2 + 1; i++)
        block_stack[i] = 0;
}


void print_block(void)
{
    int i;

    for(i = 0; i < cell_width; i++)
        printf("█");
}


void print_spaces(int count)
{
    int i;

    for(i = 0; i < count; i++)
        printf(" ");
}


void print_target_marks(int count)
{
    int i;

    for(i = 0; i < count; i++)
        printf("-");
}


void play_land_sound(void)
{
    Beep(420, 45);
}


void play_height_sound(void)
{
    Beep(750, 70);
}


void play_clear_sound(void)
{
    Beep(523, 90);
    Beep(659, 90);
    Beep(784, 150);
}


void play_game_over_sound(void)
{
    Beep(392, 100);
    Beep(330, 100);
    Beep(262, 180);
}


void end_animation(int clear_success, int count)
{
    int row;
    int inside_width;

    inside_width = box_length * cell_width;

    Sleep(300);

    for(row = 0; row < box_height; row++)
    {
        gotoxy(
            board_x + 1,
            board_y + 1 + row
        );

        print_spaces(inside_width);

        Sleep(55);
    }

    if(clear_success)
    {
        gotoxy(
            board_x + (board_width / 2) - 5,
            board_y + 6
        );

        printf("GAME CLEAR");

        gotoxy(
            board_x + (board_width / 2) - 6,
            board_y + 8
        );

        printf("높이 %2d / %2d",
               max_block(),
               TARGET_HEIGHT);
    }
    else
    {
        gotoxy(
            board_x + (board_width / 2) - 4,
            board_y + 6
        );

        printf("GAME OVER");

        gotoxy(
            board_x + (board_width / 2) - 6,
            board_y + 8
        );

        printf("높이 %2d / %2d",
               max_block(),
               TARGET_HEIGHT);
    }

    gotoxy(
        board_x + (board_width / 2) - 6,
        board_y + 11
    );

    printf("R   : RESTART");

    gotoxy(
        board_x + (board_width / 2) - 6,
        board_y + 13
    );

    printf("ESC : EXIT");

    draw_status(count, 0);
}


int wait_end_choice(void)
{
    int key;

    while(1)
    {
        key = getch();

        if(key == 'r' || key == 'R')
            return ACTION_RESTART;

        if(key == 27)
            return ACTION_EXIT;

        if(key == 0 || key == 0xE0)
            getch();
    }
}
