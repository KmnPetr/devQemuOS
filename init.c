#include <errno.h>
#include <stdio.h>
#include <sys/mount.h>
#include <sys/reboot.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bash.c"

/* Create the mount point and mount a kernel virtual filesystem. */
static void mount_fs(const char *source, const char *target, const char *type)
{
	if (mkdir(target, 0755) && errno != EEXIST)
		perror(target);
	if (mount(source, target, type, 0, NULL))
		perror(target);
}

/* Power off the machine. Returns 1 if reboot() failed. */
static int poweroff(void)
{
	fflush(stdout);
	sync();
	reboot(RB_POWER_OFF);
	perror("reboot");
	return 1;
}

int main(void)
{
	puts("Hello World");
	fflush(stdout);

	mount_fs("proc", "/proc", "proc");
	mount_fs("sysfs", "/sys", "sysfs");
	mount_fs("devtmpfs", "/dev", "devtmpfs");

	run_bash();
	return poweroff();
}
