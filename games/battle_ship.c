// author : Buyandelger.J
// date : 23/11/2025 20:12
// title :  Random Battle ship
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 10
#define SHIP_COUNT 3

int SHIP[3][4] = {
    {1, 0, 1, 0},
    {1, 1, 1, 101},
    {1, 0, 1, 0}};

// ANSI өнгөөр ялгах нь
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_UNDER "\033[4m"

#define FG_BLUE "\033[34m"
#define FG_CYAN "\033[36m"
#define FG_YELLOW "\033[33m"
#define FG_RED "\033[31m"
#define FG_GREEN "\033[32m"
#define FG_WHITE "\033[37m"
#define FG_MAGENTA "\033[35m"

#define BG_BLUE "\033[44m"
#define BG_CYAN "\033[46m"

// Тоглох үеийн мэдээлэл тодорхойлогч
#define EMPTY 0
#define MISS 1
#define HIT 2

typedef struct
{
    int id;
    int positions[12][2];
    int size;
    int head_r, head_c;
    int hits;
    int destroyed;
} Ship;

int board[SIZE][SIZE]; // онгоц буудах талбай
int tried[SIZE][SIZE]; // 0 оногдоогүй, MISS (1) эсвэл HIT (2)-г харуулах буюу оносон үгүйг илтгэх нь
Ship ships[SHIP_COUNT];
int total_ships = SHIP_COUNT;

void print_board(int reveal);
int rotate_and_collect(int rot, int out_h, int out_w, int pattern_h, int pattern_w, int positions[][2], int *size, int *head_index);
int can_place_ship_with_rotation(int b[SIZE][SIZE], int r, int c, int rot, int pattern_h, int pattern_w);
void place_ship_with_rotation(int b[SIZE][SIZE], int r, int c, int rot, int pattern_h, int pattern_w, int ship_id, Ship *ship);
int all_destroyed();
int in_bounds(int r, int c);
void reveal_ship(Ship *s);
void print_legend();

int main()
{
    memset(board, 0, sizeof(board));
    memset(tried, 0, sizeof(tried));
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        ships[i].id = i + 1;
        ships[i].size = 0;
        ships[i].hits = 0;
        ships[i].destroyed = 0;
        ships[i].head_r = ships[i].head_c = -1;
    }

    srand((unsigned)time(NULL));

    printf(ANSI_BOLD FG_CYAN "Battleship — %dx%d board, %d ships\n" ANSI_RESET, SIZE, SIZE, SHIP_COUNT);
    print_legend();

    const int PAT_H = 3, PAT_W = 4;

    int placed = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = 50; // нийт таах боломж

    while (placed < SHIP_COUNT && attempts < MAX_ATTEMPTS)
    {
        int r = rand() % SIZE; // мөрийн индекс
        int c = rand() % SIZE; // баганын индекс
        int rot = rand() % 4;  // 0,1,2,3 => 0°,90°,180°,270° => ямар өнцгөөр тавих вэ

        if (can_place_ship_with_rotation(board, r, c, rot, PAT_H, PAT_W))
        {
            place_ship_with_rotation(board, r, c, rot, PAT_H, PAT_W, placed + 1, &ships[placed]);
            placed++;
        }
        attempts++;
    }

    if (placed < SHIP_COUNT)
    {
        fprintf(stderr, "Failed to place all ships after %d attempts. Try again.\n", attempts);
        return 1;
    }

    printf(FG_GREEN "All ships placed. Let the hunt begin.\n\n" ANSI_RESET);

    while (!all_destroyed())
    {
        print_board(0);
        int row, col;
        printf("\nEnter coordinates (row col) between 1 and %d: ", SIZE);
        if (scanf("%d %d", &row, &col) != 2)
        {
            // Clear bad input
            int cch;
            while ((cch = getchar()) != EOF && cch != '\n')
                ;
            printf(FG_RED "Invalid input. Enter two integers.\n" ANSI_RESET);
            continue;
        }
        row--;
        col--;

        if (!in_bounds(row, col))
        {
            printf(FG_RED "Coordinates out of range. Use 1-%d.\n" ANSI_RESET, SIZE);
            continue;
        }

        if (tried[row][col] != 0)
        {
            printf(FG_YELLOW "You already tried that spot.\n" ANSI_RESET);
            continue;
        }

        if (board[row][col] == EMPTY)
        {
            tried[row][col] = MISS;
            printf(FG_BLUE "💧 Miss!\n" ANSI_RESET);
        }
        else
        {
            int sid = board[row][col];
            Ship *s = &ships[sid - 1];

            // өмнө онож байсан эсэхийг шалгах
            if (tried[row][col] == HIT)
            {
                printf(FG_YELLOW "You already hit that tile before.\n" ANSI_RESET);
                continue;
            }

            // онгоцны толгой эсэхийг шалгах
            if (row == s->head_r && col == s->head_c)
            {
                // бүтэн онгоцыг ил болгох
                reveal_ship(s);
                printf(FG_MAGENTA ANSI_BOLD "💥 You hit the HEAD! Ship #%d destroyed and revealed!\n" ANSI_RESET, s->id);
            }
            else
            {
                // оносон хэсгийг харуулах
                tried[row][col] = HIT;
                s->hits++;
                printf(FG_RED "💥 Hit!\n" ANSI_RESET);
                if (s->hits >= s->size)
                {
                    // онгоцны бүх хэсэг оногдвол онгоцыг ил болгох
                    reveal_ship(s);
                    printf(FG_MAGENTA ANSI_BOLD "🎯 Ship #%d fully destroyed!\n" ANSI_RESET, s->id);
                }
            }
        }
    }

    printf(ANSI_BOLD FG_GREEN "\n🎉 All ships have been destroyed! You win!\n\n" ANSI_RESET);
    printf("Final board :\n");
    print_board(1);
    return 0;
}

// Өнгөөр хэвлэх
void print_legend()
{
    printf("Legend: "
           "%s~%s = water, "
           "%sX%s = miss, "
           "%s*%s = hit, "
           "%sS%s = sunk ship \n\n",
           FG_BLUE, ANSI_RESET,   // ~ water
           FG_CYAN, ANSI_RESET,   // X miss
           FG_RED, ANSI_RESET,    // * hit
           FG_MAGENTA, ANSI_RESET // S sunk
    );
}

// Координатууд хязгаарт байгаа эсэхийг шалгах
int in_bounds(int r, int c)
{
    return (r >= 0 && r < SIZE && c >= 0 && c < SIZE);
}

// Тоглоомын самбарыг хэвлэх. Хэрэв оновол == 1 бол бүх хөлөг онгоц болон мужуудыг харуулах
void print_board(int reveal)
{
    printf("\n    ");
    for (int i = 1; i <= SIZE; i++)
        printf("%2d ", i);
    printf("\n   +");
    for (int i = 0; i < SIZE; i++)
        printf("---");
    printf("+\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%2d | ", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            if (reveal)
            {
                if (board[i][j] == EMPTY)
                {
                    printf(FG_BLUE "~ " ANSI_RESET " ");
                }
                else
                {
                    int sid = board[i][j];
                    Ship *s = &ships[sid - 1];
                    if (s->destroyed)
                    {
                        if (i == s->head_r && j == s->head_c)
                        {
                            printf(FG_MAGENTA ANSI_BOLD "H " ANSI_RESET " ");
                        }
                        else
                        {
                            printf(FG_MAGENTA "S " ANSI_RESET " ");
                        }
                    }
                    else
                    {
                        if (tried[i][j] == HIT)
                        {
                            printf(FG_RED "*" ANSI_RESET " ");
                        }
                        else
                        {
                            printf(FG_YELLOW "s " ANSI_RESET " ");
                        }
                    }
                }
            }
            else
            {
                if (tried[i][j] == MISS)
                {
                    printf(FG_CYAN "X " ANSI_RESET " ");
                }
                else if (tried[i][j] == HIT)
                {
                    printf(FG_RED "* " ANSI_RESET " ");
                }
                else
                {
                    int show_here = 0;
                    if (board[i][j] != EMPTY)
                    {
                        Ship *s = &ships[board[i][j] - 1];
                        if (s->destroyed)
                            show_here = 1;
                    }
                    if (show_here)
                    {
                        Ship *s = &ships[board[i][j] - 1];
                        if (i == s->head_r && j == s->head_c)
                            printf(FG_MAGENTA ANSI_BOLD "H " ANSI_RESET " ");
                        else
                            printf(FG_MAGENTA "S " ANSI_RESET " ");
                    }
                    else
                    {
                        printf(FG_BLUE "~ " ANSI_RESET " ");
                    }
                }
            }
        }
        printf("|\n");
    }

    printf("   +");
    for (int i = 0; i < SIZE; i++)
        printf("---");
    printf("+\n");
}

int all_destroyed()
{
    for (int i = 0; i < total_ships; i++)
        if (!ships[i].destroyed)
            return 0;
    return 1;
}

void reveal_ship(Ship *s)
{
    if (s->destroyed)
        return;
    for (int k = 0; k < s->size; k++)
    {
        int rr = s->positions[k][0];
        int cc = s->positions[k][1];
        tried[rr][cc] = HIT;
    }
    s->destroyed = 1;
    s->hits = s->size;
}

/*
Энэ функц нь онгоцны хэв маягийг (SHIP array) авч, эргүүлэх(rot) үед ямар координатуудыг эзлэхийг тооцоолно.
Мөн онгоцны толгой (head) хаана байгааг олж хадгалдаг.
*/
int rotate_and_collect(int rot, int out_h, int out_w, int pattern_h, int pattern_w, int positions[][2], int *size, int *head_index)
{
    int cnt = 0; // онгоц байгаа талбайнуудыг тоолж байгаа
    *head_index = -1;
    for (int i = 0; i < pattern_h; i++)
    {
        for (int j = 0; j < pattern_w; j++)
        {
            int val = SHIP[i][j];
            if (val == 0)
                continue; // // хоосон талбайг орхих
            int rr, cc;
            switch (rot)
            {
            case 0: // 0°
                rr = i;
                cc = j;
                break;
            case 1: // 90° цагийн зүүний дагуу -> (i,j) -> (j, pattern_h-1-i)
                rr = j;
                cc = pattern_h - 1 - i;
                break;
            case 2: // 180°
                rr = pattern_h - 1 - i;
                cc = pattern_w - 1 - j;
                break;
            case 3: // 270° цагийн зүүний дагуу -> (i,j) -> (pattern_w-1-j, i)
                rr = pattern_w - 1 - j;
                cc = i;
                break;
            default:
                return 0;
            }

            positions[cnt][0] = rr;
            positions[cnt][1] = cc;
            if (val > 100)
            {
                // байрлах эргэлтийн дараах онгоцны толгойны байршил
                *head_index = cnt;
            }
            cnt++;
        }
    }

    *size = cnt;
    return 1;
}

// Байршил нь хязгаар давахгүй, бусад хөлөг онгоцонд давхцахгүй эсвэл хүрэхгүй байгаа эсэхийг шалгана
int can_place_ship_with_rotation(int b[SIZE][SIZE], int r, int c, int rot, int pattern_h, int pattern_w)
{
    // Эргэлдсэн хайрцагны хэмжээг тодорхойлох
    // 90° эргэх үед хэмжээ нь солигдоно, бусад үед норм хэвээр
    int out_h = (rot % 2 == 0) ? pattern_h : pattern_w;
    int out_w = (rot % 2 == 0) ? pattern_w : pattern_h;

    if (r + out_h > SIZE || c + out_w > SIZE)
        return 0;

    // эргэлтийн дараа байрлалыг цуглуулах
    int positions[12][2]; // SHIP нь 3×4 → 12 ширхэг cell, хоёр координатаас бүрддэг
    int size = 0, head_index = -1;
    rotate_and_collect(rot, out_h, out_w, pattern_h, pattern_w, positions, &size, &head_index);

    // Хавтан бүрийн хувьд эргэн тойрон дахь 8 хөрш нь шүргэлцэж/давхцаж байгаа эсэхийг шалгана.
    for (int k = 0; k < size; k++)
    {
        int rr = r + positions[k][0];
        int cc = c + positions[k][1];
        if (!in_bounds(rr, cc))
            return 0;
        if (b[rr][cc] != EMPTY)
            return 0;

        // хажуугийн зайг шалгах (хоорондоо хүрэхээс сэргийлэх)
        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                int nr = rr + dr, nc = cc + dc;
                if (!in_bounds(nr, nc))
                    continue;
                if (b[nr][nc] != EMPTY)
                    return 0;
            }
        }
    }

    return 1;
}

// Хөлөг онгоцыг эргэлттэй байрлуулж, хөлөг онгоцны бүтцэд мета өгөгдлийг тэмдэглэнэ
void place_ship_with_rotation(int b[SIZE][SIZE], int r, int c, int rot, int pattern_h, int pattern_w, int ship_id, Ship *ship)
{
    int out_h = (rot % 2 == 0) ? pattern_h : pattern_w;
    int out_w = (rot % 2 == 0) ? pattern_w : pattern_h;

    int positions[12][2];
    int size = 0, head_index = -1;
    rotate_and_collect(rot, out_h, out_w, pattern_h, pattern_w, positions, &size, &head_index);

    ship->id = ship_id;
    ship->size = size;
    ship->hits = 0;
    ship->destroyed = 0;
    ship->head_r = ship->head_c = -1;

    for (int k = 0; k < size; k++)
    {
        int rr = r + positions[k][0];
        int cc = c + positions[k][1];
        b[rr][cc] = ship_id;
        ship->positions[k][0] = rr;
        ship->positions[k][1] = cc;

        if (k == head_index)
        {
            ship->head_r = rr;
            ship->head_c = cc;
        }
    }
}