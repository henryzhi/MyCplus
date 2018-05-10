#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <assert.h>
#include <sys/mman.h>
int main()
{
	int fd = open("./test", O_RDONLY);
	assert(fd >= 0);
	struct stat st;
	int rc = fstat(fd, &st);
	assert(rc == 0);
	uintptr_t data = (uintptr_t) mmap(NULL, st.st_size, PROT_READ, MAP_SHARED|MAP_POPULATE, fd, 0);
	assert(data != (uintptr_t)MAP_FAILED);
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)data;
	uintptr_t load_start = 0x400000;
	uintptr_t virt_addr = data + ehdr->e_entry - load_start;
	printf("e_entry addr:%lx\n", ehdr->e_entry);
	printf("virt addr content:%lx\n", *(uint64_t *)virt_addr);
	printf("mmaped content:%lx\n", *(uint64_t *)data);
	return 0;

}
