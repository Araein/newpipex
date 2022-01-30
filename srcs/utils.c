#include "ft_pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ((l + p + 1)));
	if (!dest)
		return (NULL);
	while (++i < l)
	{
		dest[i] = s1[i];
	}
	while (++j < p)
	{
		dest[i] = s2[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
