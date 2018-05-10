#include <unistd.h>
#include <stdio.h>
extern char template_start[];
extern char template_end[];
asm(".pushsection .text, \"ax\", @progbits\n"
    ".global template_start\n"
    ".global template_end\n"
    "template_start:\n"
    // Call write()
    "movl $1, %eax\n"  // __NR_write
    "movl $1, %edi\n"  // arg 1: stdout
    "leaq string(%rip), %rsi\n"  // arg 2: string
    "movl $string_end - string, %edx\n"  // arg 3: length of string
    "syscall\n"
    "loop:\n"
    // Call exit()
    "movl $231, %eax\n"  // __NR_exit_group
    "movl $99, %edi\n"  // arg 1: exit value
    "syscall\n"
    "jmp loop\n"

    "string: .string \"Escape!\\n\"\n"
    "string_end:\n"
    "template_end:\n"
    ".popsection\n");

int main() {

	static const char msg[] = "Hello world\n";
	if (write(1, msg, sizeof(msg) - 1)) {}
	printf("template size:%ld", template_end - template_start);
	return 44;
}
