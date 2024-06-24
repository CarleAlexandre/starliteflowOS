# include "image.h"
# include "limine.h"
# include <stdint.h>

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

void drawMandelBrot(struct limine_framebuffer *framebuffer) {
	const uint32_t palette[5] = {0xffffff, 0xffee00, 0x00eeff, 0x00ff00, 0x0000ff};
	const int max_iteration = 10;
	for (uint64_t y = 0; y < framebuffer->height; y++) {
		for (uint64_t x = 0; x < framebuffer->width; x++) {
			int iteration = 0;
			float x0 = x / framebuffer->width;
			float y0 = y / framebuffer->height;
			float a = 0.0;
			float b = 0.0;
			while (a * a + b * b <= 4 && iteration < max_iteration) {
				float tmp = a * a - b * b + x0;
				b = 2 * a * b + y0;
				a = tmp;
				iteration++;
			}
			volatile uint32_t *fb_ptr = framebuffer->address;
			fb_ptr[y * framebuffer->width + x] = palette[iteration % sizeof(palette)];
		}
	}
}

