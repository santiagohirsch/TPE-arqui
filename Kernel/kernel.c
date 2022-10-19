#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <naiveRTC.h>
#include <idtLoader.h>
#include <time.h>
#include <defs.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

static int getFormat(int n) {
	int dec = n & 240;
	dec = dec >> 4;
	int units = n & 15;
	return dec * 10 + units;
}

/*static const uint8_t charHexMap[256] = 
    {       
          0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    0xF0,    '    ',
        'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',    0,     'A',       'S',
        'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',    0,    0,  '\\',   'Z',  'X',     'C',       'V',
        'B',  'N',  'M',  ',',  '.',  '/',    0,  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
    };*/

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	
	load_idt();
	ncClear();
	/*
	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();
	ncPrint("[Finished]");
	ncNewline();
	*/
	ncPrintTextColor("Arquitectura de las Computadoras", WHITE, GREEN);
	ncNewline();
	ncPrintDec(getFormat(_NRTCGetHours()));
	ncPrint(":");
	ncPrintDec(getFormat(_NRTCGetMins()));
	ncPrint(":");
	ncPrintDec(getFormat(_NRTCGetSeconds()));
	ncNewline();
	while(seconds_elapsed() <= 5){
		; //Espero 5 segundos para que se pueda ver lo que esta impreso
	}
	ncClear();
	int secondsAnt = -1;
	int seconds;
	while(seconds_elapsed() <= 15){
		seconds = seconds_elapsed();
		if (seconds % 5 == 0 && secondsAnt != seconds){
			ncPrint("Imprimiendo nuevo mensaje ");
			ncPrintDec(seconds);
			ncNewline();
			secondsAnt = seconds;
		}
	}
	ncClear();
	char * stdout = "stdout";
	char * stderr = "stderr";
	sys_write(1, stdout, _strlen(stdout));
	ncNewline();
	sys_write(2, stderr, _strlen(stderr));
	while(seconds_elapsed() <= 5 + seconds){
		; //Espero 5 segundos para que se pueda ver lo que esta impreso
	}
	seconds = seconds_elapsed();
	ncClear();
	ncPrint("Cuando se borre este mensaje vas a tener libertad de escribir lo que quieras,");
	ncNewline();
	ncPrint("tenes que terminar la ejecucion a mano");
	while(seconds_elapsed() <= 5 + seconds){
		; //Espero 5 segundos para que se pueda ver lo que esta impreso
	}
	ncClear();
	while(1){
		;
	}
	return 0;
}
