#include <syscallDispatcher.h>

uint64_t syscallDispatcher(uint64_t *r[REGISTERS])
{
    switch (*r[RAX])
    {
    case 0:
        read(r[RDI], *r[RSI]);
        break;

    case 1:
        write(r[RDI], *r[RSI], *r[RDX], *r[RCX]);
        break;
    }
    return 0;
}

void read(uint64_t *buff, uint64_t length)
{
    char *keyboardBuffer = getKeyboardBuffer();

    for (int i = 0; i < length && keyboardBuffer[i] != 0; i++)
    {
        ((char *)buff)[i] = keyboardBuffer[i];
    }

    clearBuffer();
}

void write(uint64_t *buff, uint64_t length, uint64_t fontColor, uint64_t background_color)
{
    if (length <= 0 || fontColor < 0 || background_color < 0)
    {
        return;
    }
    print((char *)buff, length, fontColor, background_color);
}
