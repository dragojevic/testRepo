#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

void
cat(int f, char *s)
{
	char buf[8192];
	long n;

	while((n=read(f, buf, (long)sizeof buf))>0)
		if(write(1, buf, n)!=n)
			perror("write error copying %s: %r", s);
	if(n < 0)
		perror("error reading %s: %r", s);
}

int
main(int argc, char *argv[])
{
	int f, i;

//	argv0 = "cat";
	if(argc == 1)
		cat(0, "<stdin>");
	else for(i=1; i<argc; i++){
		f = open(argv[i], O_RDONLY);
		if(f < 0)
			perror("can't open %s: %r", argv[i]);
		else{
			cat(f, argv[i]);
			close(f);
		}
	}
	return 0;
}
