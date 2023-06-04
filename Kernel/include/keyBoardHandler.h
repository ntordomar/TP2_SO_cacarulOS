#define CTRL 29 //ascii for ctrl key
#define RELEASE 128 // el offset entre el codigo de una tecla y el codigo del release de esa tecla

static const char keyBoardTable[256] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', '-', '=', 8, ' ', 'Q', 'W', 'E', 'R',
        'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0,
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
        '\'', 0, 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
        'M', ',', '.', '/', 0, '*', 0, ' ', 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 4, 0, 0, 2, 0, 3, 0, 0,
        5, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // 2: left arrow
        // 3: right arrow
        // 4: up arrow
        // 5: down arrow
};

void keyHandler();

char nextElement();

void keyboardHandlerInit();

//from interrupts.asm
void _snapshot_registers();
