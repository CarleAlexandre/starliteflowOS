/*
 * =====================================================================================
 *
 *       Filename:  memory.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/24 21:32:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fatmeat (), pathofyggdrasil@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "limine.h"

__attribute__((used, section(".requests")))
static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void memory_map() {
	volatile struct limine_memmap_entry *page[4096];

	volatile struct limine_memmap_response *mmap = memmap_request.response; 
	if (!mmap) {
		hcf();
	}

	int k = 0;

	for (int i = 0; i < mmap->entry_count; i++) {
		if (mmap->entries[i]->type == 0) {
			page[k] = mmap->entries[i];
			k++;
		}
	}

};

