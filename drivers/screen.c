#include "screen.h"
#include "ports.h"

/*int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


void kprint_at(char* message, int col, int row){
    int offset;
    if(col >= 0 && row >= 0){
        offset = get_offset(col, row);
    }else{
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    int i = 0;
    while(message[i] != 0){
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    
}

void kprint(char* message){
    kprint_at(message, -1, -1);
}


int print_char(char c, int col, int row, char attr){
    unsigned char* vidmem = (unsigned char*) VIDEO_ADDRESS;
    if(!attr){
        attr = WHITE_ON_BLACK;
    }
    if(col >= MAX_COLS || row >= MAX_ROWS){
        vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 2] = 'E'; // put a red E on the end of the screen if there's a memory fault
        vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 1] = RED_ON_WHITE;
        return get_offset(col, row);
    }
    int offset;
    if(col >= 0 && row >= 0){
        offset = get_offset(col, row);
    }else{
        offset = get_cursor_offset();
    }
    
    if(c == '\n'){ // start a new line
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }else{
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    
    return offset;
    
}


void clear_screen(){
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char* screen = VIDEO_ADDRESS;
    for(i = 0; i < screen_size; i++){
        screen[i * 2] = ' '; // each cell has two bytes
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}



void set_cursor_offset(int offset){
    offset /= 2; // each cell takes two bytes, so it has to be converted to this format to communicate with 0x3d4/5
    port_byte_out(REG_SCREEN_CTRL, 14); // signal that we're writing the low byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8)); // (bbbb0000) -> (0000bbbb), which is the correct format of storage
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff)); // push the low byte to the end
}

int get_cursor_offset(){
    port_byte_out(REG_SCREEN_CTRL, 14); // write 14 to 0x3d4 to get the most significant byte
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; // (0000bbbb) -> (bbbb0000)
    port_byte_out(REG_SCREEN_CTRL, 15); // write 15 to 0x3d4 to get the least significant byte
    offset += port_byte_in(REG_SCREEN_DATA); // (bbbb0000) + (0000xxxx) -> (bbbbxxxx), the location
    return offset * 2; // since the cell location takes two bytes
}

int get_offset(int col, int row){
    return 2 * (row * MAX_COLS + col); // remember that there's a zeroth row
}

int get_offset_row(int offset){
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset){
    return (offset - 2 * get_offset_row(offset) * MAX_COLS) / 2;
}*/





int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory 
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
int print_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }