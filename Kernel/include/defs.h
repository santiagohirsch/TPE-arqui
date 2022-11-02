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
#define WHITE   0xFFFFFF
#define BLACK   0x000000
#define GREY    0x7F7F7F
#define BLUE    0xFFFFFF
#define GREEN   0x00FF00
#define RED     0x0000FF
#define YELLOW  0x00FFFF
#define CYAN    0xFFFF00
#define ORANGE  0x00A5FF
#define PINK    0xCBC0FF  

/* File Descriptors */
#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define KBDIN  3

#endif