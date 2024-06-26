#ifndef IMAGE_H
# define IMAGE_H

#include "limine.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct s_image {
	unsigned int height, width;
	uint32_t *data;
} t_image;

typedef struct s_vec2 {
	uint32_t x,y;
}t_vec2;

typedef struct s_vec3 {
	uint32_t x,y,z;
}t_vec3;

void drawImage(const t_vec2 pos, const t_image *image);
void initFrameBuffer(struct limine_framebuffer *framebuffer);
void clearFrameBuffer(struct limine_framebuffer *framebuffer);
void clearBuffer(uint32_t color);
void renderFrameBuffer(struct limine_framebuffer *framebuffer);
void clearImage(t_image *image, uint32_t color);

#endif

