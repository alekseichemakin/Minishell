#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*new;

	if (newsize <= sizeof (ptr))
		return (ptr);
	new = malloc(newsize);
	if (!new)
		return (NULL);
	if (ptr == 0)
		return (new);
	new = ft_memcpy(new, ptr, sizeof (ptr));
	free (ptr);
	return (new);
}
