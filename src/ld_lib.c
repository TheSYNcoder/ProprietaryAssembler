#include <ld_lib.h>

// 1 MiB
#define BUFFER_SIZE 1024 * 1024

int link(const char *input_file, const char *output_file)
{
    int magic, magic_end;
    int opcode_len, modification_record_len;
    char buffer[BUFFER_SIZE] = {0};
    int ifd = open(input_file, O_RDONLY);
    if (ifd == -1)
    {
        perror("open");
        return -1;
    }

    int len = read(ifd, (void *)buffer, sizeof(buffer));
    close(ifd);

    magic = *((int *)buffer);
    if (magic != MAGIC)
    {
        fprintf(stderr, "Magic bytes don't match");
        return -1;
    }
    opcode_len = *((int *)(buffer + 4));
    modification_record_len = *((int *)(buffer + 8));

    int md_offset = CODE_OFFSET + opcode_len;
    for (int i = 0; i < modification_record_len; i++)
    {
        modification_record md = *((modification_record *)(buffer + md_offset + i * sizeof(modification_record)));
        word relative_address = md.value;
        int offset = md.offset;
        word current_value = *((word *)(buffer + CODE_OFFSET + offset));
        word linked_address = START + relative_address + current_value;
        *((word *)(buffer + CODE_OFFSET + offset)) = linked_address;
    }

    char out_buffer[BUFFER_SIZE] = {0};
    int ptr = 0;
    for (int i = CODE_OFFSET; i < CODE_OFFSET + opcode_len; i++)
    {
        out_buffer[ptr++] = buffer[i];
    }

    int ofd = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (ofd == -1)
    {
        perror("open");
        return -1;
    }
    int ret = write(ofd, out_buffer, ptr);
    close(ofd);

    return 0;
}
