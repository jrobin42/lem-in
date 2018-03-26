	if (next)
	{
		(*path)->next = next->next;
		free(((t_path*)next->content)->path);
		free((t_path*)next->content);
		free(next);
	}

