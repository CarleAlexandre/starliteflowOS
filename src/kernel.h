/*
 * =====================================================================================
 *
 *       Filename:  kernel.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/24/24 19:11:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fatmeat (), pathofyggdrasil@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef KERNEL_H
# define KERNEL_H

extern void enable_fpu(void);
extern void disable_fpu(void);

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void hcf(void);

typedef enum {
	ansi_black = 0x00000000, // black
    ansi_red = 0x00aa0000, // red
    ansi_green = 0x0000aa00, // green
    ansi_brown = 0x00aa5500, // brown
    ansi_blue = 0x000000aa, // blue
    ansi_magenta = 0x00aa00aa, // magenta
    ansi_cyan = 0x0000aaaa, // cyan
    ansi_gray = 0x00aaaaaa,
} ansi_colore;

#endif

