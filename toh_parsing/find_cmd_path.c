#include "minishell.h"

static char		*find_directory(t_data *data, t_cmd *curr) // 명령어 경로 디렉토리 찾아서 문자열 저장
{
	DIR				*dp;
	struct dirent	*entry;
	char			*directory;
	int		i;

	i = 0;
	directory = 0;
	while (data->path[i])
	{
		dp = opendir(data->path[i]);
		if (dp == 0)
			return (0);
		while ((entry = readdir(dp)) != 0)
		{
			if (!ft_strcmp(entry->d_name, curr->argv[0]))
				directory = ft_strdup(data->path[i]);
		}
		closedir(dp);
		i++;
	}
	return (directory);
}

int		find_cmd_path(t_data *data, t_cmd *curr) // 명령어 경로 검색 및 수정
{
	char	*directory;

	directory = find_directory(data, curr);
	if (directory == 0)
		return (0);
	directory = ft_strjoin_free_s1(&directory, "/");
	directory = ft_strjoin_free_s1(&directory, curr->argv[0]);
	free(curr->argv[0]);
	curr->argv[0] = directory;
	return (1);
}

int		find_cmd_absolute_path(t_data *data, t_cmd *curr) //절대경로에 프로그램이 있는지 확인
{
	struct stat		buf;
	int				ret;

	ret = stat(curr->argv[0], &buf);
	if (ret == -1)
	{
		printf("bash: %s: No such file or directory\n", curr->argv[0]);
		return (0);
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("bash: %s: is a directory\n", curr->argv[0]);
			return (0);
		}
	}
	return (1);
}