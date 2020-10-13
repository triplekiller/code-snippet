/*
 * Test whether read(), fread() or mmap() are faster.
 *
 * cc -Wall -O3 read-vs-mmap.c -o read-vs-mmap
 *
 * https://eklausmeier.wordpress.com/2016/02/03/performance-comparison-mmap-versus-read-versus-fread/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_BUF 65536

int fread_test(char *pname, char *fname)
{
	char buf[MAX_BUF] = {0};
	int i, n, result = 0;

	FILE *fp = fopen(fname, "r");
	if (!fp) {
		printf("%s: cannot open %s\n", pname, fname);
		exit(1);
	}

	while ((n = fread(buf, 1, MAX_BUF, fp)) > 0) {
		for (i = 0; i < n; i++)
			result += buf[i];
	}

	if (fclose(fp) != 0) {
		printf("%s: cannot close %s\n", pname, fname);
		exit(1);
	}

	return result;
}

int mmap_test(char *pname, char *fname)
{
	int fd;
	char *p;
	int i, result = 0;
	struct stat st;

	if ((fd = open(fname, O_RDONLY)) < 0) {
		printf("%s: cannot open %s\n", pname, fname);
		exit(1);
	}

	if (fstat(fd, &st) != 0) {
		printf("%s: cannot stat %s\n", pname, fname);
		exit(1);
	}

	p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0);
	if (p == MAP_FAILED) {
		printf("%s: cannot mmap %s\n", pname, fname);
		exit(1);
	}

	for (i = st.st_size; i > 0; i--)
		result += *p++;

	if (close(fd) < 0) {
		printf("%s: cannot close %s\n", pname, fname);
		exit(1);
	}

	return result;
}

int read_test(char *pname, char *fname)
{
	int fd;
	char buf[MAX_BUF] = {0};
	int i, n, result = 0;

	if ((fd = open(fname, O_RDONLY)) < 0) {
		printf("%s: cannot open %s\n", pname, fname);
		exit(1);
	}

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		for (i = 0; i < n; i++)
			result += buf[i];
	}

	if (close(fd) < 0) {
		printf("%s: cannot close %s\n", pname, fname);
		exit(1);
	}

	return result;
}

int main(int argc, char **argv)
{
	int c, fc_id = 0;
	int (*func[])(char *pname, char *fname) = { fread_test, mmap_test, read_test };

	while ((c = getopt(argc, argv, "fmr")) != -1) {
		switch (c) {
		case 'f':
			fc_id = 0;
			break;
		case 'm':
			fc_id = 1;
			break;
		case 'r':
			fc_id = 2;
			break;
		default:
			printf("%s: unknown option %c\n", argv[0], c);
			return 1;
		}
	}

	printf("optind=%d, fc_id=%d\n", optind, fc_id);

	if (optind >= argc) {
		printf("%s: filename expected\n", argv[0]);
		return 1;
	}

	printf("The answer is: %d\n", func[fc_id](argv[0], argv[optind]));
	return 0;
}
