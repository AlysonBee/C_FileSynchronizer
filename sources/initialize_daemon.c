


#include "../includes/file_sync.h"

/*
**  Code for daemonizing a process.
*/

void	daemonize_process(void)
{
	pid_t	pid;
	pid_t	sid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	umask(0);
	sid = setsid();
	if (sid < 0)
		exit(EXIT_FAILURE);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

/* 
** Checking that the daemon lock file isn't present and an agent
** isn't currently running.
*/

bool	check_for_daemon_lock_file(void)
{
	struct dirent	*directory_info;
	DIR				*directory_pointer;
	
	if (!(directory_pointer = opendir("/tmp")))
		return (false);
	while ((directory_info = readdir(directory_pointer)))
	{
		if (strcmp(directory_info->d_name, "daemon.lock") == 0)
		{
			(void)closedir(directory_pointer);
			return (true);
		}
	}
	(void)closedir(directory_pointer);
	return (false);
}

/*
** Create an initial daemon process.
*/

int		initialize_daemon(void)
{
	int	lock_file_fd;
	int	log_file_fd;

	// check if a daemon isn't already running.
	if (check_for_daemon_lock_file() == true)
		exit(1);

	// create daemon.lock file
	lock_file_fd = open("/tmp/daemon.lock", O_RDONLY);
	close(lock_file_fd);	

	// create log files to write checkpoint info to.
	log_file_fd = open("logs/daemon.logs", O_RDWR);
	
	return (log_file_fd);
}
