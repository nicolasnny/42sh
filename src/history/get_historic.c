/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to get the last commands written in the shell
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "struct.h"

static linked_list_t *return_read_error(int fd)
{
    perror("Read error");
    close(fd);
    return NULL;
}

static void setup_final_array(char **final_array, char **file_by_line,
    char *cmd)
{
    final_array = my_strstrcpy(final_array, file_by_line);
    final_array[my_strstrlen(file_by_line)] = cmd;
    final_array[my_strstrlen(file_by_line) + 1] = NULL;
}

static linked_list_t *add_command_to_end(char *buffer, char *cmd)
{
    char **file_by_line = NULL;
    char **final_array = NULL;

    file_by_line = my_pimp_str_to_wa(buffer, "\n");
    free(buffer);
    if (file_by_line == NULL) {
        free(cmd);
        return NULL;
    }
    final_array = malloc(sizeof(char *) * (my_strstrlen(file_by_line) + 2));
    if (final_array == NULL) {
        free_str_array(file_by_line);
        perror("add command to end malloc");
        free(cmd);
        return NULL;
    }
    setup_final_array(final_array, file_by_line, cmd);
    free_str_array(file_by_line);
    return create_list_from_array(final_array);
}

int check_buffer(char const *buffer, int fd)
{
    if (buffer == NULL) {
        close(fd);
        perror("get array from prev command malloc");
        return ERROR;
    }
    return SUCCESS;
}

static linked_list_t *prev_cmd_end(int fd, char *buffer,
    char *current_cmd, int file_size)
{
    int chars_read = 0;

    chars_read = read(fd, buffer, file_size - 1);
    if (chars_read == SYS_ERROR) {
        free(current_cmd);
        return return_read_error(fd);
    }
    close(fd);
    buffer[chars_read] = '\0';
    return add_command_to_end(buffer, current_cmd);
}

linked_list_t *get_array_from_prev_cmd(char *current_cmd)
{
    int fd = read_history(HISTORIC_FILENAME);
    char *buffer = NULL;
    int file_size = get_file_size(HISTORIC_FILENAME);

    if (fd == ERROR || file_size <= 0) {
        free(current_cmd);
        return NULL;
    }
    buffer = malloc(sizeof(char) * (file_size + 1));
    if (check_buffer(buffer, fd) == ERROR) {
        free(current_cmd);
        return NULL;
    }
    return prev_cmd_end(fd, buffer, current_cmd, file_size);
}
