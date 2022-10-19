#include <naiveConsole.h>
#include <defs.h>


static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

static int checkAttribute(int background, int foreground){
	return (background >= 0 && background <= 0xF && foreground >= 0 && foreground <= 0xF);
}

void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintChar(char character)
{
	if (character == '\n'){
		ncNewline();
	} else if (character == 0x7F){ //backspace mapeado como 0x7F
		if (currentVideo < 0xB8002){
			return;
		}
		currentVideo -= 2;
		*currentVideo = ' ';
	} else {
		*currentVideo = character;
		currentVideo += 2;	
	}
}

void ncPrintTextColor(const char * string, int background, int foreground){
	if (!checkAttribute(background, foreground)){
		return;
	}
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintCharColor(string[i], background, foreground);
}

void ncPrintCharColor(char character, int background, int foreground){
	int attribute = background*16 + foreground; /* En los bits bajos tiene el color del foreground y 
												** en los altos el background. Queda armado así:
												** 0xBackFore
												*/
	*currentVideo++ = character;
	*currentVideo++ = attribute; 
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++){
		video[i * 2] = ' ';
		video[(i * 2) + 1] = DEFAULT;
	}
	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


void write(unsigned int fd, char *buf, int count){
	if (fd == STDOUT){
		int i;
		for (i = 0; i < count; i++){
			ncPrintChar(buf[i]);
		}	
	} else if (fd == STDERR){
		int i;
		for (i = 0; i < count; i++){
			ncPrintCharColor(buf[i], BLACK, RED);
		}
	}
}