#include "parser.h"
#include "libft.h"

static int is_space(char character)
{
    return character == ' ' || character == '\t' || character == '\r';
}

static char *copy_string(const char *text)
{
    char *copy = malloc(ft_strlen(text) + 1);
    if (copy != NULL)
        ft_strlcpy(copy, text, ft_strlen(text) + 1);
    return copy;
}

static int parse_number(const char *text, int *number)
{
    long value = 0;
    int digits = 0;
    while (*text >= '0' && *text <= '9') {
        value = value * 10 + (*text - '0');
        if (value > 2147483647L)
            return 0;
        digits = 1;
        text++;
    }
    if (!digits || *text != '\0')
        return 0;
    *number = (int)value;
    return 1;
}

static char *trim(char *text)
{
    char *end;
    while (is_space(*text))
        text++;
    end = text + ft_strlen(text);
    while (end > text && is_space(end[-1]))
        *--end = '\0';
    return text;
}

static int parse_room(char *text, char *name, int name_size)
{
    int length = 0;
    while (*text && !is_space(*text) && *text != '-') {
        if (length + 1 >= name_size)
            return 0;
        name[length++] = *text++;
    }
    name[length] = '\0';
    while (is_space(*text))
        text++;
    if (!length || !*text)
        return 0;
    while (*text && !is_space(*text))
        text++;
    while (is_space(*text))
        text++;
    if (!*text)
        return 0;
    while (*text && !is_space(*text))
        text++;
    while (is_space(*text))
        text++;
    return *text == '\0';
}

int parse_file(Graph *graph, int *ants, char **start_room, char **end_room)
{
    char *line;
    int ants_read = 0;
    int next_start = 0;
    int next_end = 0;

    while ((line = get_next_line(0)) != NULL) {
        char *text;
        char *newline = ft_strchr(line, '\n');
        if (newline)
            *newline = '\0';
        text = trim(line);
        if (*text == '\0')
        {
            free(line);
            continue;
        }
        if (*text == '#' && !(text[1] == '#' && text[2] != '\0'))
        {
            free(line);
            continue;
        }
        if (!ants_read) {
            if (!parse_number(text, ants))
            {
                free(line);
                return 0;
            }
            ants_read = 1;
            free(line);
            continue;
        }
        if (ft_strncmp(text, "##start", 8) == 0 && text[8] == '\0') {
            next_start = 1;
            free(line);
            continue;
        }
        if (ft_strncmp(text, "##end", 6) == 0 && text[6] == '\0') {
            next_end = 1;
            free(line);
            continue;
        }

        char *separator = ft_strchr(text, '-');
        if (separator != NULL) {
            *separator = '\0';
            char *from = trim(text);
            char *to = trim(separator + 1);
            if (*from != '\0' && *to != '\0')
                graph_add_link(graph, from, to);
            free(line);
            continue;
        }

        char name[256];
        if (parse_room(text, name, sizeof(name))) {
            graph_add_node(graph, name);
            if (next_start) {
                free(*start_room);
                *start_room = copy_string(name);
                next_start = 0;
            } else if (next_end) {
                free(*end_room);
                *end_room = copy_string(name);
                next_end = 0;
            }
        }
        free(line);
    }
    return ants_read && *start_room != NULL && *end_room != NULL;
}
