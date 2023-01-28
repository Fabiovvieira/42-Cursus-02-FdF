/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:18:36 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/01/27 17:29:17 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

void	ft_lstprint(t_list **lst);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_sa(t_list **lst);
void	ft_sb(t_list **lst);
void	ft_ss(t_list **lst_a, t_list **lst_b);
t_list	*ft_ra(t_list *lst);
t_list	*ft_rb(t_list *lst);
void	ft_rr(t_list **lst_a, t_list **lst_b);
t_list	*ft_rra(t_list *lst);
t_list	*ft_rrb(t_list *lst);
void	ft_rrr(t_list **lst_a, t_list **lst_b);
void	ft_pb(t_list **lst_a, t_list **lst_b);
void	ft_pa(t_list **lst_b, t_list **lst_a);
void	apply_func(t_list **lst_a, t_list **lst_b, char *str);

int		min_index(t_list **lst);
int		max_index(t_list **lst);
void	check_indexmin_partition(int *flag, int i, int *imin, int size);
int		get_index_partition(t_list **lst, int partition);

int		insert_node(t_list **lst, char *str);
t_list	*ft_nodenew(void *content);
int		check_dup(t_list **lst, long num);
int		ft_strisdigit(char *str);
void	free_stacks(t_list **lst);

void	look_for_contentmin(t_list *tmp, long *contentmin, t_list **aux);
void	sort_indexation(t_list **lst);
void	last_move(t_list **lst_a, t_list **lst_b);
void	sort_3(t_list **lst);
void	sort_2(t_list **lst);

void	aux_laspart(t_list **lst_a, t_list **lst_b, int *index, int size);
void	ft_sort_lastp(t_list **lst_a, t_list **lst_b, int (*func)(t_list **));
void	check_num_part(t_list **lst_a, t_list **lst_b, int multpart, int part);

void	ft_sort_plus_100(t_list **lst_a, t_list **lst_b, int partition);
void	move_up_push(t_list **lst_a, t_list **lst_b, int *index, int *size);
void	move_down_push(t_list **lst_a, t_list **lst_b, int *index, int *size);

void	ft_sort_less_100(t_list **lst_a, t_list **lst_b);
void	move_and_push_b(t_list **lst_a, t_list **lst_b, int *m_i, int *size);

void	free_split(char **list);
void	select_sort(t_list **stack_a, t_list **stack_b, int size);
int		insert_with_split(t_list **stack_a, char ***list, char **argv);
int		insert_with_multiarg(t_list **stack_a, int argc, char **argv);

int		check_sort(t_list *stack_a);

#endif
