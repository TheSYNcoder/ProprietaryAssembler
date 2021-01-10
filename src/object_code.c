#include <object_code.h>

// #ifndef SECOND_PASS_PARSE_H
// line parse_intermediate_file(const char *filename)
// {
//     int N = 6;
//     line res;
//     res.len = N;
//     res.tokens = (second_pass_token *)malloc(N * sizeof(sizeof(second_pass_token)));
//     res.tokens[0].type = O, res.tokens[0].value = 0x80;
//     res.tokens[1].type = R, res.tokens[1].value = 0x01;
//     res.tokens[2].type = S, res.tokens[2].value = 0;
//     res.tokens[3].type = O, res.tokens[3].value = 0x83;
//     res.tokens[4].type = L, res.tokens[4].value = 0x1234;
//     res.tokens[5].type = DW, res.tokens[5].value = 0x13;
//     return res;
// }
// #endif

// 1 MiB
#define BUFFER_SIZE (1024 * 1024)
int write_object_file(const char *object_file, line tokens_array)
{
    int n = tokens_array.len;
    int fd = open(object_file, O_RDWR | O_TRUNC | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    double_word magic = MAGIC;
    char buffer[BUFFER_SIZE] = {0};
    modification_record modification_buffer[1024] = {0};
    int ptr = 0;
    int mod_ptr = 0;

    for (int i = 0; i < n; i++)
    {
        second_pass_token token = tokens_array.tokens[i];
        switch (token.type)
        {
            byte last_code = 0x00;
            byte res_b;
            word res_w, symbol_address;
            double_word res_d;
            int index;
        case O:
            res_b = token.value;
            buffer[ptr++] = res_b;
            last_code = res_b;
            break;
        case R:
            // res_b = token.value;
            // buffer[ptr++] = res_b;
            break;
        case L:
            if (last_code == 0xcd)
            {
                res_b = token.value;
                buffer[ptr++] = res_b;
            }
            else
            {
                res_w = token.value;
                buffer[ptr++] = (byte)(res_w & (0xFF));
                buffer[ptr++] = (byte)((res_w >> 8) & (0xFF));
            }
            break;
        case S:
            index = token.value;
            symbol_address = symbol_table[index].LC;
            // printf("%s %d %d\n", symbol_table[index].label, symbol_address, __LINE__);
            modification_record mr = {M, ptr, symbol_address};
            modification_buffer[mod_ptr++] = mr;
            buffer[ptr++] = 0x00;
            buffer[ptr++] = 0x00;
            break;
        case DB:
            res_b = token.value;
            buffer[ptr++] = res_b;
            break;
        case DW:
            res_w = token.value;
            buffer[ptr++] = (byte)(res_w & (0xFF));
            buffer[ptr++] = (byte)((res_w >> 8) & (0xFF));
            break;
        case DD:
            res_d = token.value;
            buffer[ptr++] = (byte)(res_d & (0xFF));
            buffer[ptr++] = (byte)((res_d >> 8) & (0xFF));
            buffer[ptr++] = (byte)((res_d >> 16) & (0xFF));
            buffer[ptr++] = (byte)((res_d >> 24) & (0xFF));
            break;
        }
    }

    int ret;
    ret = write(fd, (void *)&magic, sizeof(magic));
    ret = write(fd, (void *)&ptr, sizeof(ptr));
    ret = write(fd, (void *)&mod_ptr, sizeof(mod_ptr));
    ret = write(fd, (void *)buffer, ptr);
    ret = write(fd, (void *)modification_buffer, (mod_ptr * sizeof(modification_record)));
    ret = write(fd, (void *)&magic, sizeof(magic));

    close(fd);

    return 0;
}

int generate_object_code(const char *intermeditate_file, const char *object_file)
{
    line tokens_array = parse_intermediate_file(intermeditate_file);
    int ret = write_object_file(object_file, tokens_array);
    return ret;
}
