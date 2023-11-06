/*
 * mycpu is freely redistributable under the MIT License. See the file
 * "LICENSE" for information on usage and redistribution of this file.
 */

#pragma once

#define VRAM_BASE 0x20000000
#define VRAM ((volatile unsigned char *) VRAM_BASE)
#define TIMER_BASE 0x80000000
#define TIMER_LIMIT ((volatile unsigned int *) (TIMER_BASE + 4))
#define TIMER_ENABLED ((volatile unsigned int *) (TIMER_BASE + 8))
