#include "main.h"

/**
 * append_var - appends var to linked list
 * @hd: linked list head
 * @s: var value
 * @l1: var length
 * @l2: value length
 * Return: the linked list address
 */

variables_t *append_var(variables_t **hd, int l1, char *s, int l2)
{
	variables_t *copy, *curr;

	copy = malloc(sizeof(variables_t));
	if (copy == NULL)
		return (NULL);

	copy->var_l = l1;
	copy->var_val = s;
	copy->val_l = l2;

	copy->next = NULL;
	curr = *hd;

	if (curr == NULL)
	{
		*hd = copy;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = copy;
	}

	return (*hd);
}

/**
 * free_vars_t - releases variables_t list
 * @hd: linked list head
 * Return: 0 - null
 */

void free_vars_t(variables_t **hd)
{
	variables_t *copy, *node;

	if (hd != NULL)
	{
		node = *hd;
		while (node != NULL)
		{
			copy = node;
			node = node->next;
			free(copy);
		}
		*hd = NULL;
	}
}
