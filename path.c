#include "shell.h"

/**
 * realloc_dptr - re-allocating the double pointer
 * @old_ptr: pointer old memory(double)
 * @size1: ptr space in byt
 * @size2: new memory space in byt
 * Return: ptr or NULL on fail
 */

char **realloc_dptr(char **old_ptr, unsigned int size1, unsigned int size2)
{
	char **to_ptr;
	unsigned int idx;

	if (old_ptr == NULL)
		return (malloc(size2 * sizeof(char *)));
	if (size2 == size1)
		return (old_ptr);

	to_ptr = malloc(size2 * sizeof(char *));
	if (to_ptr == NULL)
		return (NULL);
	for (idx = 0; idx < size1; idx++)
		to_ptr[idx] = old_ptr[idx];

	free(old_ptr);
	return (to_ptr);
}

/**
 * _realloc - reallocating memor
 * @old_ptr: pointer old memory
 * @size1: ptr space in byt
 * @size2: new meory space in byt
 * Return: ptr or NULL on fail
 */

void *_realloc(void *old_ptr, unsigned int size1, unsigned int size2)
{
	void *to_ptr;

	if (old_ptr == NULL)
		return (malloc(size2));
	if (size2 == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (size2 == size1)
		return (old_ptr);

	to_ptr = malloc(size2);
	if (to_ptr == NULL)
		return (NULL);
	if (size2 < size1)
		_memcpy(to_ptr, old_ptr, size2);
	else
		_memcpy(to_ptr, old_ptr, size1);

	free(old_ptr);

	return (to_ptr);
}


/**
 * _memcpy - copies information from one pointer to the other
 * @to_ptr: new pointer
 * @old_ptr: previous pointer
 * @ptr_size: size of destination pointer
 * Return: 0 - null
 */

void _memcpy(void *to_ptr, const void *old_ptr, unsigned int ptr_size)
{
	unsigned int idx;
	char *old = (char *)old_ptr, *new = (char *)to_ptr;

	for (idx = 0; idx < ptr_size; idx++)
		new[idx] = old[idx];
}
