/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** user_input.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "shell.h"
#include "struct.h"

char *get_user_input(shell_info_t *my_shell)
{
    char *user_input = get_prompt();

    putchar('\n');
    if (!user_input) {
        my_shell->exit_shell = true;
        free(user_input);
        return NULL;
    }
    if (my_strlen(user_input) == 0) {
        free(user_input);
        return NULL;
    }
    return user_input;
}

char ***get_all_cmd(char ***all_cmds, char **args)
{
    int num_cmds = 0;
    char **args_cpy = my_str_array_dup(args);

    for (int i = 0; args[i]; i++)
        num_cmds++;
    all_cmds = malloc((num_cmds + 1) * sizeof(char **));
    if (all_cmds == NULL) {
        perror("get_all_cmds malloc failed");
        return NULL;
    }
    for (int i = 0; i <= num_cmds; i++) {
        all_cmds[i] = NULL;
    }
    for (int i = 0; args_cpy[i]; i++) {
        all_cmds[i] = my_pimp_str_to_wa(args_cpy[i], " ");
    }
    free_str_array(args_cpy);
    return all_cmds;
}

static bool no_cmd(char *user_input)
{
    for (int i = 0; user_input[i] != '\0'; i++) {
        if (user_input[i] != ' ' && user_input[i] != '\t') {
            return false;
        }
    }
    return true;
}

char **get_args(shell_info_t *my_shell)
{
    char *user_input = get_user_input(my_shell);
    char *user_input_cpy = my_strdup(user_input);
    char **args = NULL;

    if (!user_input || no_cmd(user_input)) {
        return NULL;
    }
    if (my_strlen(user_input) != 0) {
        args = my_pimp_str_to_wa(user_input, ";");
    }
    if (my_strcmp(args[0], "exit") == 0) {
        printf("exit\n");
        my_shell->exit_shell = true;
        my_shell->exit_status = 0;
        args = NULL;
    }
    my_free_n_str(2, user_input, user_input_cpy);
    return args;
}
