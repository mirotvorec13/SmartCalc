#ifndef S21_STRUCT_DATA_H
#define S21_STRUCT_DATA_H

#define BRACKET_OPEN 0
#define BRACKET_CLOSE 1
#define IS_X 12

typedef struct oper_node {
  struct oper_node *next;

  char *oper_str;
  int priority;

  int args_count;
  double (*func_one_arg)(double x);
  double (*func_two_arg)(double x, double y);

} oper_node;

typedef struct oper_list {
  oper_node *start;
  oper_node *end;
} oper_list;

oper_list *oper_list_create();
void oper_list_free(oper_list *list);
oper_node *oper_list_find(oper_list *list, char **oper_str);

#endif
