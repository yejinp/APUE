BEGIN {
	printf("#include <errno.h>\n");
	printf("#include <limits.h>\n");
	printf("\n");
	printf("static void pr_sysconf(char *, int);\n");
	printf("\n");
	printf("int\n");
	printf("main(int argc, char *argv[])\n");
	printf("{\n");
	printf("\tif(argc != 2)\n");
	printf("\t\tprintf(\"usage: a.out <dirname>\");\n\n");

}
