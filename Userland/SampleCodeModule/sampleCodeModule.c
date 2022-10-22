// DUDASSS: aca van funciones en part o llamamos a kernel?
//#define LENGTH_PARAMETERS
//#define BUFFER_LENGTH 
// EXCEPCIONES ACAA!! : division por cero y codigo d op invalido
/* dsps brancheo y las copio ahi mauro no me retes
static void divideByZero(){ //=> hay q dividir ..?

}
static void invalidOPCode(){

}
*/

/*
static void commandHelp(){
	if (cantParams != 0){
		wrongOPCodeexception();
	}
	run_help();
}

static void commandRTC(){
	run_RTC();
}*/


//static const char* commands[] = {"clear", "divideandconquer", "dividebyzero", "fractal", "help", "inforeg", "invalidopcode", "printmem", "time"};
//static void (*commands_functions[])(char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS]) = {clear, divideAndConquer, divideByZero, fractal, help, inforeg, invalidOPCode, printMem, time};

#include <libVid.h>

int main() {
	/*
	>>
	$> help

	array de strings  (tron, screenshot, rtc, checkExcep, screenshot , inforeg, post32, changeFontSize, etc )
	$> rtc
	hora del dia
	$> tron
	limpia la pantalla y la ocupa con el tron
	*/

	//hacer el print
	print("bienvenido: type help for options");
	while(1){
		//inicializar vec d comandos ??

		//buffer para ver q comando me manda
		//char buff_command[BUFFER_LENGTH] = {0};
		//scan(buff_command,BUFFER_LENGTH); -> hay q hacerlo nosotros :) :)  
		  
		 
	}
	return 0;
	
}