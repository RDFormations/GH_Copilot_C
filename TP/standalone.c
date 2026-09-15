/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standalone.c                                       :+:      :+:    :+:   */
/*                                                                            */
/*   Standalone push_swap checker — single file, no libft/libstack deps.      */
/*   Build: cc -Wall -Wextra standalone.c -o checker                          */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef OPEN_MAX
# define OPEN_MAX 16
#endif

# define BUFFER_SIZE 1024
# define STACK_BUFFER 1024
# define INSTRUCTIONS_BUFFER_SIZE 4096

typedef struct s_stack
{
	int				top;
	unsigned int	size;
	int				*array;
}	t_stack;

typedef void (*t_op_fn)(t_stack *a, t_stack *b);

typedef struct s_op
{
	const char	*name;
	t_op_fn		fn;
}	t_op;

/* --- string utils -------------------------------------------------------- */

static size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	str_cmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static bool	str_eq(const char *s1, const char *s2)
{
	return (str_cmp(s1, s2, str_len(s2) + 1) == 0);
}

static void	put_str_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, str_len(s));
}

static void	put_endl_fd(const char *s, int fd)
{
	put_str_fd(s, fd);
	write(fd, "\n", 1);
}

static void	mem_zero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}

static void	mem_cpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
}

static char	*str_dup(const char *s)
{
	char	*out;
	size_t	i;

	out = malloc(str_len(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static char	*str_sub(const char *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	slen;

	slen = str_len(s);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && start + i < slen)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static char	*str_join(const char *s1, const char *s2)
{
	char	*out;
	size_t	i;
	size_t	j;
	size_t	len1;

	len1 = str_len(s1);
	out = malloc(len1 + str_len(s2) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	return (out);
}

static char	*str_chr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	is_space(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/* --- get_next_line ------------------------------------------------------- */

static int	gnl_result(char **line, char **saved, int fd, int readed)
{
	size_t	len;
	char	*tmp;

	if (readed < 0)
		return (-1);
	if (readed == 0 && !saved[fd] && *line)
		return (0);
	len = 0;
	while (saved[fd] && saved[fd][len] && saved[fd][len] != '\n')
		len++;
	if (saved[fd] && saved[fd][len] == '\n')
	{
		*line = str_sub(saved[fd], 0, len);
		tmp = str_dup(&saved[fd][len + 1]);
		free(saved[fd]);
		saved[fd] = tmp;
		if (saved[fd] && !saved[fd][0])
		{
			free(saved[fd]);
			saved[fd] = NULL;
		}
		return (1);
	}
	if (saved[fd])
	{
		*line = str_dup(saved[fd]);
		free(saved[fd]);
		saved[fd] = NULL;
	}
	return (0);
}

static void	gnl_paste(char **saved, char *buff)
{
	char	*tmp;

	tmp = str_join(*saved, buff);
	free(*saved);
	*saved = tmp;
}

static int	get_next_line(int fd, char **line)
{
	static char	*saved[OPEN_MAX];
	char		*buff;
	int			readed;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed < 0)
			break ;
		buff[readed] = '\0';
		if (!saved[fd])
			saved[fd] = str_dup(buff);
		else
			gnl_paste(&saved[fd], buff);
		if (str_chr(buff, '\n'))
			break ;
	}
	free(buff);
	return (gnl_result(line, saved, fd, readed));
}

/* --- split --------------------------------------------------------------- */

static int	word_count(const char *str, char c)
{
	int	trigger;
	int	count;

	trigger = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && !trigger)
		{
			trigger = 1;
			count++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (count);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	word = malloc((size_t)(finish - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**str_split(const char *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		index;

	split = malloc((size_t)(word_count(s, c) + 1) * sizeof(*split));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= str_len(s))
	{
		if (s[i] != c && index < 0)
			index = (int)i;
		else if ((s[i] == c || !s[i]) && index >= 0)
		{
			split[j++] = word_dup(s, index, (int)i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

/* --- stack --------------------------------------------------------------- */

static t_stack	*stack_init(unsigned int size)
{
	t_stack	*stack;

	stack = malloc(sizeof(*stack));
	if (!stack)
		return (NULL);
	stack->array = malloc(size * sizeof(*stack->array));
	if (!stack->array)
	{
		free(stack);
		return (NULL);
	}
	stack->size = size;
	stack->top = -1;
	return (stack);
}

static void	stack_swap(t_stack *stack)
{
	int	aux;

	if (stack->top <= 0)
		return ;
	aux = stack->array[stack->top];
	stack->array[stack->top] = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = aux;
}

static void	stack_push(t_stack *from, t_stack *to)
{
	if (from->top == -1)
		return ;
	to->array[++to->top] = from->array[from->top--];
}

static void	stack_rotate(t_stack *stack)
{
	unsigned int	i;
	int				tmp;

	if (stack->top < 0)
		return ;
	i = (unsigned int)stack->top + 1;
	tmp = stack->array[stack->top];
	while (--i)
		stack->array[i] = stack->array[i - 1];
	stack->array[0] = tmp;
}

static void	stack_rev_rotate(t_stack *stack)
{
	int	i;
	int	tmp;

	if (stack->top < 0)
		return ;
	i = -1;
	tmp = stack->array[0];
	while (++i < stack->top)
		stack->array[i] = stack->array[i + 1];
	stack->array[stack->top] = tmp;
}

static void	free_array(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	free(stack->array);
	free(stack);
}

static void	exit_error(t_stack *stack, char **ops, int status)
{
	free_stack(stack);
	free_array((void **)ops);
	put_str_fd("Error\n", STDERR_FILENO);
	exit(status);
}

static void	reverse_array(int *array, size_t size)
{
	size_t	i;
	int		tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = tmp;
		i++;
	}
}

static bool	is_sorted(t_stack *stack)
{
	int	i;

	i = 0;
	while (i < stack->top)
	{
		if (stack->array[i + 1] > stack->array[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	atoiv(const char *str, int *n)
{
	int		sign;
	bool	overflow;

	*n = 0;
	sign = -1;
	overflow = false;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = 1;
	while (*str >= '0' && *str <= '9')
	{
		*n = *n * 10 - (*str++ - '0');
		if (*n > 0 || (*n == INT_MIN && sign < 0))
			overflow = true;
	}
	*n *= sign;
	return (overflow);
}

static bool	validate_int(char *elem)
{
	unsigned int	i;
	unsigned int	cm;

	i = 0;
	cm = 0;
	while (elem[i])
	{
		if (elem[i] == '-' && cm < 1)
			cm++;
		else if (!is_digit(elem[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	already_exists(int n, t_stack *stack)
{
	int	i;

	i = stack->top;
	while (i >= 0)
	{
		if (stack->array[i] == n)
			return (true);
		i--;
	}
	return (false);
}

static int	fill_element(t_stack *stack, char *arg)
{
	char	**array;
	unsigned int	j;
	int				n;
	int				status;

	j = 0;
	status = 0;
	array = str_split(arg, ' ');
	if (!array)
		return (1);
	while (array[j] && !status)
	{
		if (validate_int(array[j]))
			status = 1;
		else if (atoiv(array[j], &n))
			status = 2;
		else if (already_exists(n, stack))
			status = 3;
		else
			stack->array[++stack->top] = n;
		j++;
	}
	free_array((void **)array);
	return (status);
}

static t_stack	*get_stack(int size, char **args)
{
	unsigned int	i;
	int				status;
	t_stack			*stack;

	if (size < 1)
		exit(0);
	i = 0;
	status = 0;
	stack = stack_init(STACK_BUFFER);
	if (!stack)
		exit(1);
	while (args[i] && !status)
		status = fill_element(stack, args[i++]);
	if (status)
	{
		free_stack(stack);
		put_endl_fd("Error", STDERR_FILENO);
		exit(status);
	}
	reverse_array(stack->array, (size_t)stack->top + 1);
	return (stack);
}

/* --- operations jump table ------------------------------------------------- */

static void	op_sa(t_stack *a, t_stack *b)
{
	(void)b;
	stack_swap(a);
}

static void	op_sb(t_stack *a, t_stack *b)
{
	(void)a;
	stack_swap(b);
}

static void	op_ss(t_stack *a, t_stack *b)
{
	stack_swap(a);
	stack_swap(b);
}

static void	op_pa(t_stack *a, t_stack *b)
{
	stack_push(b, a);
}

static void	op_pb(t_stack *a, t_stack *b)
{
	stack_push(a, b);
}

static void	op_ra(t_stack *a, t_stack *b)
{
	(void)b;
	stack_rotate(a);
}

static void	op_rb(t_stack *a, t_stack *b)
{
	(void)a;
	stack_rotate(b);
}

static void	op_rr(t_stack *a, t_stack *b)
{
	stack_rotate(a);
	stack_rotate(b);
}

static void	op_rra(t_stack *a, t_stack *b)
{
	(void)b;
	stack_rev_rotate(a);
}

static void	op_rrb(t_stack *a, t_stack *b)
{
	(void)a;
	stack_rev_rotate(b);
}

static void	op_rrr(t_stack *a, t_stack *b)
{
	stack_rev_rotate(a);
	stack_rev_rotate(b);
}

static const t_op	g_ops[] = {
	{"sa", op_sa},
	{"sb", op_sb},
	{"ss", op_ss},
	{"pa", op_pa},
	{"pb", op_pb},
	{"ra", op_ra},
	{"rb", op_rb},
	{"rr", op_rr},
	{"rra", op_rra},
	{"rrb", op_rrb},
	{"rrr", op_rrr},
	{NULL, NULL}
};

static bool	invalid_instruction(char *op)
{
	size_t	i;

	i = 0;
	while (g_ops[i].name)
	{
		if (str_eq(op, g_ops[i].name))
			return (false);
		i++;
	}
	return (true);
}

static void	run_instruction(char *op, t_stack *a, t_stack *b)
{
	size_t	i;

	i = 0;
	while (g_ops[i].name)
	{
		if (str_eq(op, g_ops[i].name))
		{
			g_ops[i].fn(a, b);
			return ;
		}
		i++;
	}
}

/* --- instructions input -------------------------------------------------- */

static int	heap_set(char ***instructions, char **buffer, int count)
{
	char			**tmp;
	static size_t	total;
	size_t			i;

	tmp = malloc((total + (size_t)count + 1) * sizeof(*tmp));
	if (!tmp)
		return (1);
	i = 0;
	while (i < total)
	{
		tmp[i] = (*instructions)[i];
		i++;
	}
	mem_cpy(tmp + total, buffer, (size_t)count * sizeof(*tmp));
	tmp[total + (size_t)count] = NULL;
	free(*instructions);
	*instructions = tmp;
	total += (size_t)count;
	return (0);
}

static int	get_instructions(char ***instructions)
{
	char	*buffer[INSTRUCTIONS_BUFFER_SIZE];
	char	*op;
	int		i;
	int		status;

	i = 0;
	status = 0;
	op = NULL;
	while (!status && get_next_line(STDIN_FILENO, &op) > 0)
	{
		if (invalid_instruction(op))
			status = 1;
		else
		{
			buffer[i++] = op;
			if (i == INSTRUCTIONS_BUFFER_SIZE)
			{
				if (heap_set(instructions, buffer, i))
					status = 1;
				mem_zero(buffer, sizeof(buffer));
				i = 0;
			}
		}
	}
	if (!status && heap_set(instructions, buffer, i))
		status = 1;
	free(op);
	return (status);
}

static int	execute(char **instructions, t_stack *a)
{
	t_stack	*b;
	char	**cursor;

	b = stack_init(a->size);
	if (!b)
		return (1);
	cursor = instructions;
	while (cursor && *cursor)
	{
		run_instruction(*cursor, a, b);
		cursor++;
	}
	if (!is_sorted(a) || b->top > -1)
		put_str_fd("KO\n", STDOUT_FILENO);
	else
		put_str_fd("OK\n", STDOUT_FILENO);
	free_stack(b);
	return (0);
}

/* --- main ---------------------------------------------------------------- */

int	main(int argc, char **argv)
{
	t_stack	*stack;
	char	**instructions;
	int		status;

	status = 0;
	instructions = NULL;
	stack = get_stack(argc - 1, &argv[1]);
	status = get_instructions(&instructions);
	if (status)
		exit_error(stack, instructions, status);
	execute(instructions, stack);
	free_array((void **)instructions);
	free_stack(stack);
	return (0);
}
