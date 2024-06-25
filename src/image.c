# include "image.h"
# include "limine.h"
# include "kernel.h"

static t_image buffer;

void writepixeltoimg(const int x, const int y, t_image *image, t_color color) {
	image->data[x + y * image->width] = color;
}

void drawImage(const t_vec2 pos, const t_image *image) {
	volatile t_color *fb_ptr = buffer.data;
	for (uint32_t y = 0; y < image->height; y++) {
		for (uint32_t x = 0; x < image->width; x++) {
			// Note: we assume the framebuffer model is RGB with 32-bit pixels.
			fb_ptr[(pos.y + y) * (buffer.width) + (pos.x + x)] = image->data[y * image->width + x];
		}
	}
}

void drawMandelBrot(struct limine_framebuffer *framebuffer) {
/*	const uint32_t palette[5] = {0xffffff, 0xffee00, 0x00eeff, 0x00ff00, 0x0000ff};
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
*/}

void initFrameBuffer(struct limine_framebuffer *framebuffer) {
	t_color data[1920 * 1080];
	buffer.width = framebuffer->width;
	if (buffer.width > 1920) buffer.width = 1920;
	buffer.height = framebuffer->height;
	if (buffer.height > 1080) buffer.height = 1080;
	buffer.data = data; 
}

void clearFrameBuffer(struct limine_framebuffer *framebuffer) {
	memset(framebuffer->address, 0x000000, sizeof(uint32_t) * framebuffer->height * framebuffer->width);
}

void clearBuffer(t_color color) {
	volatile t_color *data = buffer.data;
	for (uint64_t i = 0; i < buffer.width * buffer.height; i++) {
		data[i] = color;
	}
}

void renderFrameBuffer(struct limine_framebuffer *framebuffer) {
	volatile uint32_t *fb_ptr = framebuffer->address;
	for (uint64_t i = 0; i < buffer.width * buffer.height; i++) {
		fb_ptr[i] = buffer.data[i].color_int;
	}
	for (uint32_t y = 0; y < buffer.height; y++) {
		for (uint32_t x = 0; x < buffer.width; x++) {
			// Note: we assume the framebuffer model is RGB with 32-bit pixels.
			fb_ptr[y * (framebuffer->pitch / 4) + x] = buffer.data[y * buffer.width + x].color_int;
		}
	}
}

