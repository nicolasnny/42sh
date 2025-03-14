/*
** EPITECH PROJECT, 2024
** unit_tests
** File description:
** function that allow me to test my program
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stddef.h>
#include "shell.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* initialisation */

Test(unit_test, set_stuct_with_good_env, .init=redirect_all_stdout)
{
    char **env = malloc(sizeof(char) * 3);
    shell_info_t *my_shell = NULL;

    env[0] = my_strdup("PATH=vehifvhu");
    env[1] = my_strdup("HOST=ezfhbvj");
    env[2] = NULL;
    my_shell = init_shell_info_t(env);
    cr_assert_not_null(my_shell);
}

Test(unit_test, set_stuct_with_env_null, .init=redirect_all_stdout)
{
    cr_assert_eq(get_file_size("src/main.c"), 271);
    cr_assert_eq(get_file_size("not existing file"), OPEN_ERROR);
}

/* display prompt */

Test(unit_test, display_prompt, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);

    disp_actual_dir(my_shell);
}

/* execution */

Test(unit_test, command_handling, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("ls");
    args[1] = strdup("-l");
    args[2] = NULL;
    command_handling(my_shell, args);
}

Test(unit_test, command_type, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char *cmd = my_strdup("ls -l && pwd");

    check_given_cmd_type(my_shell, cmd);
}

/* color*/

Test(unit_test, valid_color, .init=redirect_all_stdout)
{
    cr_assert_eq(valid_color("red"), 31);
    cr_assert_eq(valid_color("blue"), 34);
    cr_assert_eq(valid_color("yellow"), 33);
    cr_assert_eq(valid_color("magenta"),35);
    cr_assert_eq(valid_color("not a color"), -1);
}

Test(unit_test, set_color, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("color");
    args[1] = strdup("blue");
    args[2] = strdup("yellow");
    args[3] = NULL;
    command_handling(my_shell, args);
    cr_assert_eq(my_shell->color[0], 34);
    cr_assert_eq(my_shell->color[1], 33);
}

Test(unit_test, color_help, .init=redirect_all_stdout)
{
    disp_color_help();
}

Test(unit_test, change_color, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("color");
    args[1] = strdup("blue");
    args[2] = strdup("yellow");
    args[3] = NULL;
    command_handling(my_shell, args);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
}

/* historic */

Test(unit_test, add_to_save, .init=redirect_all_stdout)
{
    cr_assert_eq(add_command_to_save("ls"), SUCCESS);
    cr_assert_eq(add_command_to_save("history"), SUCCESS);
    cr_assert_eq(add_command_to_save("egregt"), SUCCESS);
    cr_assert_eq(add_command_to_save("test"), SUCCESS);
    cr_assert_eq(add_command_to_save("echo something"), SUCCESS);
}

Test(unit_test, special_get_nbr, .init=redirect_all_stdout)
{
    cr_assert_eq(my_special_getnbr("e124to"), 124);
    cr_assert_eq(my_special_getnbr("124to"), 124);
    cr_assert_eq(my_special_getnbr("-e124to"), 124);
    cr_assert_eq(my_special_getnbr("e-1to"), -1);
    cr_assert_eq(my_special_getnbr("eto"), 0);
}

Test(unit_test, check_if_history, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **cmd = create_strstr("!", "5", NULL, NULL);

    check_if_historic(cmd, my_shell);
}

Test(unit_test, getcmd_with_str, .init=redirect_all_stdout)
{
    char *cmd = my_strdup("ls -l test_dir");

    get_cmd_with_str(cmd);
}

Test(unit_test, add_cmd_to_historic, .init=redirect_all_stdout)
{
    char *cmd = my_strdup("ls -l test_dir");

    cr_assert_not_null(get_array_from_prev_cmd(cmd));
}

Test(unit_test, create_list, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("1 09:54 cd", "1 09:54 cd", "1 09:54 cd", "1 09:54 cd");

    cr_assert_not_null(create_list_from_array(args1));
}

Test(unit_test, read_history, .init=redirect_all_stdout)
{
    cr_assert_eq(read_history("zojr"), SYS_ERROR);
}

Test(unit_test, check_if_cmd_needs_to_be_replaced, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("ls -l", NULL, NULL, NULL);
    char **args2 = create_strstr("ls -la", NULL, NULL, NULL);

    cr_assert_str_eq(check_if_historic(args1, my_shell), "ls -l");
    cr_assert_str_eq(check_if_historic(args2, my_shell), "ls -la");
}

Test(unit_test, find_last_cmd, .init=redirect_all_stdout)
{
    cr_assert_not_null(find_last_cmd());
}

/* pipe */

Test(unit_test, simple_pipe_command, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char *cmd = my_strdup("ls tests/test_dir | cat -e");

    check_pipe(cmd, my_shell);
    cr_assert_stdout_eq_str("file$\n");
    free(cmd);
    free_str_array(env);
}

Test(unit_test, disp_historic, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("1 09:54 cd", "1 09:54 cd", "1 09:54 cd", "1 09:54 cd");

    display_historic(args1, my_shell);
}

/* local variables */

Test(unit_test, set_new_var, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("set", "name=nicolas", "no_value", "empty=");

    set_local(args, my_shell);
}

Test(unit_test, set_existing_var, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **set = create_strstr("set", "name=nicolas", "no_value", "empty=");
    char **new_set = create_strstr("set", "name=nunney", "no_value", "empty");

    set_local(set, my_shell);
    set_local(new_set, my_shell);
}

Test(unit_test, disp_local, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **set = create_strstr("set", "name=nicolas", "no_value", "empty=");
    char **new_set = create_strstr("set", "name=nunney", "no_value", "empty");
    char **disp = malloc(sizeof(char *) * 2);

    disp[0] = my_strdup("set");
    disp[1] = NULL;

    set_local(set, my_shell);
    set_local(new_set, my_shell);
    set_local(disp, my_shell);
}

Test(unit_test, unset_new_var, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **set = create_strstr("set", "name=nicolas", "no_value", "empty=");
    char **unset = create_strstr("unset", "name", "no_value", "empty");

    set_local(set, my_shell);
    unset_local(unset, my_shell);
}

/* redirects */

Test(unit_test, redirects, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **simple_right = create_strstr("ls", ">", "test", NULL);
    char **double_right = create_strstr("ls", ">>", "test", NULL);
    char **simple_left = create_strstr("ls", "<", "test", NULL);
    char **double_left = create_strstr("ls", "<<", "test", NULL);

    simple_left = check_redirect(simple_left, my_shell);
    double_left = check_redirect(double_left, my_shell);
    simple_right = check_redirect(simple_right, my_shell);
    double_right = check_redirect(double_right, my_shell);
    cr_assert_eq(my_strstrlen(simple_left), 1);
    cr_assert_eq(my_strstrlen(simple_right), 1);
    cr_assert_eq(my_strstrlen(double_right), 1);
    cr_assert_eq(my_strstrlen(double_left), 1);
}

Test(unit_test, redirects_bad_args, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **simple_right1 = create_strstr(">", "test", NULL, NULL);
    char **double_right1 = create_strstr("ls", ">>", NULL, NULL);
    char **simple_left1 = create_strstr("<", "toto", NULL, NULL);
    char **double_left1 = create_strstr("ls", "<<", NULL, NULL);
    char **simple_right2 = create_strstr("ls", ">", NULL, NULL);
    char **double_right2 = create_strstr(">>", "test", NULL, NULL);
    char **simple_left2 = create_strstr("ls", "<", NULL, NULL);
    char **double_left2 = create_strstr("<<", "tata", NULL, NULL);

    simple_left1 = check_redirect(simple_left1, my_shell);
    double_left1 = check_redirect(double_left1, my_shell);
    simple_right1 = check_redirect(simple_right1, my_shell);
    double_right1 = check_redirect(double_right1, my_shell);
    simple_left2 = check_redirect(simple_left2, my_shell);
    double_left2 = check_redirect(double_left2, my_shell);
    simple_right2 = check_redirect(simple_right2, my_shell);
    double_right2 = check_redirect(double_right2, my_shell);
}

/* cd */

Test(unit_test, cd_to_a_dir, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("cd", "test_dir", NULL, NULL);

    change_dir(args, my_shell);
}

Test(unit_test, cd_to_root, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("cd", NULL, NULL, NULL);

    change_dir(args, my_shell);
    my_shell->env = NULL;
    change_dir(args, my_shell);
    my_shell->env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "TOTO=tata", "NB=lo");
    change_dir(args, my_shell);
}

Test(unit_test, cd_to_last_dir, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("cd", "/tmp", NULL, NULL);
    char **args2 = create_strstr("cd", "-", NULL, NULL);

    change_dir(args1, my_shell);
    my_shell->last_path = my_strdup("/home");
    change_dir(args2, my_shell);
}

Test(unit_test, cd_bad_args, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("cd", "/tmp", "/dev", NULL);

    change_dir(args1, my_shell);
}

/* var insertion */

Test(unit_test, replace_var, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("cd", "$HOME/delivery", "$TEST", NULL);
    char **args2 = create_strstr("cd", "$HOME/delivery", "$toto", NULL);

    args1 = replace_var(args1, my_shell);
    args2 = replace_var(args2, my_shell);
    cr_assert_str_eq(args1[1], "/home//delivery");
    cr_assert_str_eq(args1[2], "toto");
    cr_assert_null(args2);
}

/* globbing */

Test(unit_test, globbing, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("ls", "*-l", NULL, NULL);
    char **args2 = create_strstr("ls", "??sh", NULL, NULL);

    globbing(args1, my_shell);
    globbing(args2, my_shell);
}


/* env variables */

Test(unit_test, setenv_basic, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("setenv", "toto", "tata", NULL);
    char **args2 = create_strstr("setenv", "tutu", NULL, NULL);
    char **args3 = create_strstr("setenv", NULL, NULL, NULL);

    set_env(args1, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "toto=tata");
    set_env(args2, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "tutu=");
    set_env(args3, my_shell);
}

Test(unit_test, setenv_bad_args, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("setenv", "toto", "tata", "NULL");
    char **args2 = create_strstr("setenv", "1tutu", NULL, NULL);
    char **args3 = create_strstr("setenv", "toto-tata", NULL, NULL);

    set_env(args1, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "TEST=toto");
    set_env(args2, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "TEST=toto");
    set_env(args3, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "TEST=toto");
}

Test(unit_test, setenv_no_disp_basic, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args1 = create_strstr("setenv", "toto", "tata", NULL);
    char **args2 = create_strstr("setenv", "tutu", NULL, NULL);
    char **args3 = create_strstr("setenv", NULL, NULL, NULL);

    set_env_no_disp(args1, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "toto=tata");
    set_env_no_disp(args2, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "tutu=");
    set_env_no_disp(args3, my_shell);
}

Test(unit_test, unset_env_basic, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **setenv = create_strstr("setenv", "toto", "tata", NULL);
    char **setenv2 = create_strstr("setenv", "tutu", NULL, NULL);
    char **unsetenv = create_strstr("unsetenv", "toto", "tutu", NULL);

    set_env(setenv, my_shell);
    set_env(setenv2, my_shell);
    unset_env(unsetenv, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "TEST=toto");
}

Test(unit_test, unset_env_no_args, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **unsetenv = create_strstr("unsetenv", NULL, NULL, NULL);

    unset_env(unsetenv, my_shell);
    cr_assert_str_eq(my_shell->env[my_strstrlen(my_shell->env) - 1], "TEST=toto");
}

/* alias */

Test(unit_test, create_alias, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("alias", "ll", "ls -l", NULL);

    my_alias(args, my_shell);
    cr_assert_str_eq(my_shell->list_alias->alias_cmd, "ll");
    cr_assert_str_eq(my_shell->list_alias->real_cmd, "ls -l");
}

Test(unit_test, remove_alias, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("alias", "ll", "ls -l", NULL);
    char **args2 = create_strstr("alias", "toto", "pwd", NULL);
    char **args3 = create_strstr("unalias", "toto", NULL, NULL);

    my_alias(args, my_shell);
    my_alias(args2, my_shell);
    del_alias(args3, my_shell);
    cr_assert_str_eq(my_shell->list_alias->alias_cmd, "ll");
    cr_assert_null(my_shell->list_alias->next);
}

Test(unit_test, alias_loop, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("alias", "ll", "ls -l", NULL);
    char **args2 = create_strstr("alias", "toto", "pwd", NULL);
    char **args3 = create_strstr("alias", "tata", "cd", NULL);

    my_alias(args, my_shell);
    my_alias(args2, my_shell);
    my_alias(args3, my_shell);
    exec_alias_loop(my_shell, my_shell->list_alias);
}

/* backtick */

Test(unit_test, backtick, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char *output = get_backtick_output(my_shell, my_strdup("echo toto"));

    cr_assert_str_eq(output, "toto ");
}

/* parentheses */

Test(unit_test, parentheses_order, .init=redirect_all_stdout)
{
    cr_assert_eq(check_parentheses_order("(ls)"), true);
    cr_assert_eq(check_parentheses_order("(ls"), false);
    cr_assert_eq(check_parentheses_order(")ls("), false);
    cr_assert_eq(check_parentheses_order(")ls((())"), false);
}

Test(unit_test, parentheses_badly_placed, .init=redirect_all_stdout)
{
    cr_assert_eq(parentheses_badly_placed("(ls)"), false);
    cr_assert_eq(parentheses_badly_placed("(ls"), false);
    cr_assert_eq(parentheses_badly_placed(")ls("), false);
    cr_assert_eq(parentheses_badly_placed(")ls((())"), false);
}

Test(unit_test, exec_parentheses, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=/bin/", "HOST=nicolo",
        "HOME=/home/", "TEST=toto");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = create_strstr("(ls)", NULL, NULL, NULL);

    cr_assert_eq(exec_parentheses(my_shell, args), true);
}