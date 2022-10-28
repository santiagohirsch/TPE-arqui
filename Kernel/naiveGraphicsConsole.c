#include <naiveGraphicsConsole.h>
#include <font.h>
#include <stdint.h>
#include <string.h>
#define FONT1 16
#define FONT2 32
#define FONT3 48
struct vbe_mode_info_structure {
    uint16_t attributes;        // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;           // deprecated
    uint8_t window_b;           // deprecated
    uint16_t granularity;       // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;      // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;         // number of bytes per horizontal line
    uint16_t width;         // width in pixels
    uint16_t height;        // height in pixels
    uint8_t w_char;         // unused...
    uint8_t y_char;         // ...
    uint8_t planes;
    uint8_t bpp;            // bits per pixel in this mode
    uint8_t banks;          // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;      // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;       // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;   // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];

    //uint8_t pixel_height; // alto del char, x1 = 16, x2 = 32
    //uint8_t pixel_width; // ancho del char, x1 = 9, x2 = 16

} __attribute__ ((packed));

struct vbe_mode_info_structure* screenData = (void*)0x5C00;



//    STATIC METHODS DECLARATION

static void* getPtrToPixel(uint16_t x, uint16_t y) {
    return (void*)(screenData->framebuffer + 3 * (x + (y * (uint64_t)screenData->width)));
}

static void delete_last_char();

uint16_t penX = 0, penY = 0;
uint16_t lastPenX = 0;
Color penColor = {0x7F, 0x7F, 0x7F};

// ==============================================================================
// PUBLIC NGC_PRINT METHODS

void changeFontSize(void){
   /* ngc_printNewline();
    ngc_printChar(screenData->pixel_height + '0');
    screenData->pixel_height++;
    ngc_printChar(screenData->pixel_height + '0');
    ngc_printNewline();
    ngc_printChar(screenData->pixel_width + '0');
    ngc_printNewline();*/
}
void ngc_printChar(char c) {
    if (c == '\n') {
        ngc_printNewline();
        return;
    } else 
    if (c == 0x7F) // BACKSPACE code
    {
        delete_last_char();
        return;
    } else
    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
	    const char* data = font + 32*(c-33);
        // cambiando h: cambio tam
	    for (int h=0; h<FONT2; h += 2) { //h a 16 queda estirado 
            //1x1 -> 4x4 -> 16x16
            // width orig (en x1) == 9
            // Imprimir en tamaño x2    
            Color* pos = (Color*)getPtrToPixel(penX, penY+h);
            Color* pos2 = (Color*)getPtrToPixel(penX, penY+h+1);
            //Color* pos3 = (Color*)getPtrToPixel(penX, penY+h+2); para q estaba muchachos ???? 
            // si el bit en cada posicion esta prendido: pinto, sino dejo
            if (*data & 0b00000001) pos[0] = penColor, pos[1] = penColor, pos2[0] = penColor, pos2[1] = penColor;       
            if (*data & 0b00000010) pos[2] = penColor, pos[3] = penColor, pos2[2] = penColor, pos2[3] = penColor;       
            if (*data & 0b00000100) pos[4] = penColor, pos[5] = penColor, pos2[4] = penColor, pos2[5] = penColor;
            if (*data & 0b00001000) pos[6] = penColor, pos[7] = penColor , pos2[6] = penColor, pos2[7] = penColor;     
            if (*data & 0b00010000) pos[8] = penColor, pos[9] = penColor , pos2[8] = penColor, pos2[9] = penColor;
            if (*data & 0b00100000) pos[10] = penColor, pos[11] = penColor, pos2[10] = penColor, pos2[11] = penColor;
            if (*data & 0b01000000) pos[12] = penColor, pos[13] = penColor, pos2[12] = penColor, pos2[13] = penColor;
            if (*data & 0b10000000) pos[14] = penColor, pos[15] = penColor, pos2[14] = penColor, pos2[15] = penColor;
            data++;
            // salteo un pixel para espacear
            if (*data & 0b00000001) pos[16] = penColor, pos[17] = penColor,  pos2[16] = penColor, pos2[17] = penColor;
            data++;
            
        /*
            Color* pos = (Color*)getPtrToPixel(penX, penY+h);
            // si el bit en cada posicion esta prendido: pinto, sino dejo
    		if (*data & 0b00000001) pos[0] = penColor;
    		if (*data & 0b00000010) pos[1] = penColor;
    		if (*data & 0b00000100) pos[2] = penColor;
    		if (*data & 0b00001000) pos[3] = penColor;
    		if (*data & 0b00010000) pos[4] = penColor;
    		if (*data & 0b00100000) pos[5] = penColor;
    		if (*data & 0b01000000) pos[6] = penColor;
    		if (*data & 0b10000000) pos[7] = penColor;
    		data++;
            // salteo un pixel para espacear
    		if (*data & 0b00000001) pos[8] = penColor;
    		data++;
            
        }*/
        }
    }
    penX += CHAR_WIDTH;
    if (penX > screenData->width - CHAR_WIDTH)
        ngc_printNewline();
}

void ngc_print(char * string){
    for(int i = 0; string[i]!= '\0';i++){
        ngc_printChar(string[i]);
    }
}

void ngc_printNewline(void) {
    lastPenX = penX;
    penX = 0; // pen x is set to full left.

    // If there is space for another line, we simply advance the pen y. Otherwise, we move up the entire screen and clear the lower part.
    if (penY + (2*CHAR_HEIGHT) <= screenData->height) {
        penY += 2*CHAR_HEIGHT;
    } else {
        //AGREGANDO X2 PARA EL NUEVO TAM
        // dst: posicion de inicio de la pantalla
        void* dst = (void*)((uint64_t)screenData->framebuffer);

        // src: ultima posicion de la pantalla 
        // (3 por rgb, CHAR_HEIGHT es el tamaño de cada linea, width es el ancho de la pantalla)
        void* src = (void*)(dst + 3 * (CHAR_HEIGHT*2 * (uint64_t)screenData->width)); //char_height*2 para el aumento del size
        
        // len: cantidad de pixeles en toda la pantalla menos la ultima linea
        // 3 por rgb, width es el ancho, height - CHAR_HEIGHT es todas las lineas excepto la ultima
        uint64_t len = 3 * ((uint64_t)screenData->width * (screenData->height*2 - CHAR_HEIGHT*2)); //height*2 char_height*2 para el aumento del size
        
        /*
            este bloque copia todo lo escrito en pantalla a una linea mas arriba
            y deja la posicion para escribir en la ultima linea
        */
        memcpy(dst, src, len);
        memset(dst+len, 0, 3 * (uint64_t)screenData->width * CHAR_HEIGHT*2); //char_height*2 para el aumento del size
    }
}
// ==============================================================================

static void delete_last_char() {
    // caso: Delete last '/n'
    if (penX == CHAR_WIDTH*2) //Para que no se pueda borrar el prompt
    {
        // caso en que DELETE fuera el primer caractér ingresado: lo omito
        //if (penY == 0) return;

// TODO: SOLO SE PUEDE BORRAR UNA LINEA CON ESTA IMPLEMENTACION
    
        /*penY -= CHAR_HEIGHT;
        penX = lastPenX;*/
        return;

    }
    // caso: Delete last char
    else {

        penX -= CHAR_WIDTH;

        Color aux = {0,0,0};
        
        for (int h=0; h<FONT2; h++) {
            // se llenan todos los pixeles del ultimo char en {0,0,0}
    		Color* pos = (Color*)getPtrToPixel(penX, penY+h);
            
            for (int i = 0 ;i < FONT2/2 ; i++){
                pos[i]=aux;
            }
    	}
    }
    
}
