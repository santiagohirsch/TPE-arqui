#ifndef DEFS_H
#define DEFS_H


/* Flags para derechos de acceso de los segmentos */
#define ACS_PRESENT     0x80            /* segmento presente en memoria */
#define ACS_CSEG        0x18            /* segmento de codigo */
#define ACS_DSEG        0x10            /* segmento de datos */
#define ACS_READ        0x02            /* segmento de lectura */
#define ACS_WRITE       0x02            /* segmento de escritura */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E		/* Interrupt GATE 32 bits */
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )


#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

/* Colores para los prints */
/*
    Color white = {0xFF, 0xFF, 0xFF};
	Color black = {0x00, 0x00, 0x00};
	Color grey = {0x7F, 0x7F, 0x7F};
	Color blue = {0xFF, 0x00, 0x00};
	Color green = {0x00, 0xFF, 0x00};
	Color red = {0x00, 0x00, 0xFF};
	Color yellow = {0x00, 0xFF, 0xFF};
	Color cyan = {0xFF, 0xFF, 0x00};
	Color orange = {0x00, 0xA5, 0xFF};
	Color pink = {0xCB, 0xC0, 0xFF};
*/
    

/* File Descriptors */
#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define KBDIN  3

#endif