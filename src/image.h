#ifndef IMAGE_H
# define IMAGE_H

#include "limine.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct s_color_rgba {
	uint8_t r, g, b, a;
} t_color_rgba;

typedef union s_color {
	t_color_rgba color;
	int32_t color_int;
} t_color;

typedef struct s_image {
	unsigned int height, width;
	t_color *data;
} t_image;

typedef struct s_vec2 {
	uint32_t x,y;
}t_vec2;

typedef struct s_vec3 {
	uint32_t x,y,z;
}t_vec3;

void drawImage(const t_vec2 pos, const t_image *image, struct limine_framebuffer *framebuffer);
void writepixeltoimg(const int x, const int y, t_image *image, t_color color);

#endif

