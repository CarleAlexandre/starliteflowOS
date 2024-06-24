# include "image.h"
# include "limine.h"
#include <stdint.h>

void writepixeltoimg(const int x, const int y, t_image *image, t_color color) {
	image->data[x + y * image->width] = color;
}

void drawImage(const t_vec2 pos, const t_image *image, struct limine_framebuffer *framebuffer) {
	for (uint32_t y = 0; y < image->height; y++) {
		for (uint32_t x = 0; x < image->width; x++) {
			// Note: we assume the framebuffer model is RGB with 32-bit pixels.
			volatile uint32_t *fb_ptr = framebuffer->address;
			fb_ptr[(pos.y + y) * (framebuffer->width) +(pos.x + x)] = image->data[y * image->width + x].color_int;
		}
	}
}

