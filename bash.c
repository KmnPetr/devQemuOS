#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>

/* Start an interactive bash and wait until it exits. */
void run_bash(void)
{
	pid_t pid;
	int status;
	int fd;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return;
	}
	if (pid == 0) {
		setsid();
		fd = open("/dev/console", O_RDWR);
		if (fd >= 0) {
			dup2(fd, STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			if (fd > STDERR_FILENO)
				close(fd);
			ioctl(STDIN_FILENO, TIOCSCTTY, 0);
		}
		setenv("PATH", "/bin:/usr/bin", 1);
		setenv("PS1", "\\w # ", 1);
		if (!getenv("TERM"))
			setenv("TERM", "linux", 1);
		execl("/bin/bash", "bash", "-i", (char *)NULL);
		perror("/bin/bash");
		_exit(127);
	}
	while (waitpid(pid, &status, 0) < 0 && errno == EINTR)
		;
}
