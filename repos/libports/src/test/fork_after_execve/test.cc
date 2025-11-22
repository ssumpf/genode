/*
 * \brief  Test fork after execve with a shared
 *         library calling a libc function.
 * \author Christian Prochaska
 * \date   2025-11-14
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

extern "C" void test_shared_lib_func();

int main(int argc, char **argv)
{
	/* first argument is 0 or 1 to indicate the instance version */
	if (argc != 2)
		return -1;

	printf("--- test-fork_after_execve started ---\n");

	int const version = atoi(argv[1]);

	if (version == 0) {

		printf("initial instance\n");

		char argv0[25];
		char argv1[25];

		snprintf(argv0, sizeof(argv0), "test-fork_after_execve");
		snprintf(argv1, sizeof(argv1), "%d", version + 1);

		char *argv[] { argv0, argv1, NULL };
		char *env[] { NULL };

		printf("calling execve()\n");

		execve("test-fork_after_execve", argv, env);

	}

	printf("instance started by execve()\n");

	printf("calling fork()\n");

	pid_t fork_ret = fork();

	if (fork_ret < 0) {
		printf("Error: fork returned %d, errno=%d\n", fork_ret, errno);
		return -1;
	}

	if (fork_ret == 0) {

		printf("instance started by fork()\n");

		printf("calling test_shared_lib_func()\n");
		test_shared_lib_func();
		printf("test_shared_lib_func() returned\n");

		return 0;

	} else {

		printf("calling test_shared_lib_func()\n");
		test_shared_lib_func();
		printf("test_shared_lib_func() returned\n");

		printf("waiting for child exit\n");

		waitpid(fork_ret, nullptr, 0);
	}

	return 0;
}
