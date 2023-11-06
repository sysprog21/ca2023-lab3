#include "mmio.h"

#define MUL80(x) (((x) << 6) + ((x) << 4))

struct {
    unsigned char row, col;
} screen;

static void copy_line(int prev, int cur)
{
    int *prev_vram_start = ((int *) (MUL80(prev) + VRAM_BASE));
    int *cur_vram_start = ((int *) (MUL80(cur) + VRAM_BASE));
    for (int i = 0; i < 20; ++i)
        prev_vram_start[i] = cur_vram_start[i];
}

static void write_char(int row, int col, unsigned char ch)
{
    VRAM[MUL80(row) + col] = ch;
}

static void new_line()
{
    screen.col = 0;
    if (screen.row == 29) {
        for (int i = 0; i < 29; ++i)
            copy_line(i, i + 1);
        int *vram = (int *) (MUL80(29) + VRAM_BASE);
        for (int i = 0; i < 20; ++i)
            vram[i] = 0x20202020;
    } else {
        ++screen.row;
    }
}

static void putch(unsigned char ch)
{
    if (ch == '\n') {
        new_line();
    } else if (ch == '\r') {
        screen.col = 0;
    } else {
        if (screen.col == 79)
            new_line();
        write_char(screen.row, screen.col, ch);
        ++screen.col;
    }
}

static void clear_screen()
{
    screen.row = 0;
    screen.col = 0;
    int *vram = ((int *) VRAM_BASE);
    for (int i = 0; i < 600; ++i)
        vram[i] = 0x20202020;
}

static void print_hex(unsigned int counter)
{
    putch('0');
    putch('x');
    for (int i = 7; i >= 0; --i) {
        unsigned int num = (counter >> (i << 2)) & 0xF;
        if (num < 10) {
            putch('0' + num);
        } else {
            putch('A' + num - 10);
        }
    }
}

static void putstr(const char *s)
{
    while (*s)
        putch(*(s++));
}

static void print_timer()
{
    putstr("Hardware timer count limit = ");
    print_hex(*TIMER_LIMIT);
    putstr(", enabled = ");
    print_hex(*TIMER_ENABLED);
    putch('\n');
}

extern void enable_interrupt();
extern unsigned int get_epc();

int main()
{
    clear_screen();
    *TIMER_ENABLED = 1;
    putstr("MyCPU Demo Program ");
    putch(137);
    putstr("Hello, world!\n");
    putstr("Last EPC = ");
    print_hex(get_epc());
    putch('\n');
    print_timer();
    *((int *) 0x4) = 0xDEADBEEF;
    enable_interrupt();

    for (;;)
        ;
}
