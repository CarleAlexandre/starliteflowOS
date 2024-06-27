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
#include "kernel.h"

__attribute__((used, section(".requests")))
static volatile struct limine_efi_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

__attribute__((used, section(".requests")))
static volatile struct limine_paging_mode_request paging_mode_request = {
	.id = LIMINE_PAGING_MODE_REQUEST,
	.revision = 0,
};

uint64_t page_directory[512] __attribute__((aligned(0x1000)));

uint64_t page_dir_ptr_table[4] __attribute__((aligned(0x20)));

void init_paging() {
	//set each entry to not present
	for(int i = 0; i < 1024; i++) {
	    // This sets the following flags to the pages:
	    //   Supervisor: Only kernel-mode can access them
	    //   Write Enabled: It can be both read from and written to
	    //   Not Present: The page table is not present
	    page_directory[i] = 0x00000002;
	}

	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	//we will fill all 1024 entries in the table, mapping 4 megabytes
	// attributes: supervisor level, read/write, present
	page_dir_ptr_table[0] = (uint64_t)&page_directory;
	page_directory[0] = 0b10000011;
	asm volatile ("movl %%cr4, %%eax; bts $5, %%eax; movl %%eax, %%cr4" ::: "eax"); // set bit5 in CR4 to enable PAE		 
	asm volatile ("movl %0, %%cr3" :: "r" (&page_dir_ptr_table)); // load PDPT into CR3
	asm volatile ("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0;" ::: "eax");//enablepaging
}

void memory_map() {
	volatile struct limine_memmap_entry *entry[4096];

	volatile struct limine_efi_memmap_response *mmap = memmap_request.response; 
	if (mmap == 0x00 || mmap->memmap_size < 1) {
		hcf();
	}

	int k = 0;

	for (int i = 0; i < mmap->entry_count; i++) {
		if (mmap->entries[i]->type == 0) {
			entry[k] = mmap->entries[i];
			k++;
		}
	}

};

