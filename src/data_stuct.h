/*
 * =====================================================================================
 *
 *       Filename:  data_stuct.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/24 17:27:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fatmeat (), pathofyggdrasil@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

typedef struct s_node {
	s_node *next;
	void *data;
} t_node;

typedef struct s_list {
	t_node *first;
	t_node *last;
	unsigned long size;
} t_list;

typedef struct s_vector {
	void *data;
	unsigned long size;
} t_vector;

typedef struct s_tree {
	void *data;
	s_tree *left;
	s_tree *right;
//	s_tree *up;
} t_tree;

# endif

