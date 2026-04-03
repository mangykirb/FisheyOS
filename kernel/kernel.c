int cursor_x = 0;
int cursor_y = 0;

unsigned char saved_char = ' ';
unsigned char saved_attr = 0x07;
// global vars cuz i dont wanna repeat them in functions

void print(const char* str, int x, int y, int attribute, int fullBLOCK) {
    unsigned char* video = (unsigned char*)0xB8000; // text mode video memory
    if (fullBLOCK == 1) {
        for(int i = 0; str[i] != '\0'; i++) {
            video[(y*80 + x + i)*2] = 219;
            video[(y*80 + x + i)*2 + 1] = attribute;
        }
        return;
    } else {
        for(int i = 0; str[i] != '\0'; i++) {
            video[(y*80 + x + i)*2] = str[i]; 
            video[(y*80 + x + i)*2 + 1] = attribute; 
        }
    }
} // more arguments than the win32 api functions like MessageBox (A or W) lol

void clean(void){
    unsigned char* video = (unsigned char*)0xB8000; 
    for (int i = 0; i < 80*25; i++)
    {
        video[i*2] = ' '; 
        video[i*2 + 1] = 0x07; 
    } // ipxe stuff into the shadow realm
    
}
void draw_cursor() {
    unsigned char* video = (unsigned char*)0xB8000;
    int pos = (cursor_y * 80 + cursor_x) * 2;

    saved_char = video[pos];
    saved_attr = video[pos + 1];


    video[pos] = 'X';
    video[pos + 1] = 0x03; // cool ass color i just decided to guess and got it
}
void erase_cursor() {
    unsigned char* video = (unsigned char*)0xB8000;
    int pos = (cursor_y * 80 + cursor_x) * 2;

    video[pos] = saved_char;
    video[pos + 1] = saved_attr;
}
void move_cursor(int dx, int dy) {
    erase_cursor();

    cursor_x += dx;
    cursor_y += dy;

    
    if(cursor_x < 0) cursor_x = 0;
    if(cursor_y < 0) cursor_y = 0;
    if(cursor_x > 79) cursor_x = 79;
    if(cursor_y > 24) cursor_y = 24;

    draw_cursor();
}
unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void kernel_main() {
    clean();

    int fullBLOCK = 219;
    int drawing = 0;
    const char* full = "                                                                                "; // yea i guess

    for (short i = 0; i < 25; i++)
    {
        print(full, 0, i, 0x03, 1);
    }

    draw_cursor(); 

    while(1) {
        if (drawing == 1) {
            draw_cursor();
        }
        if(!(inb(0x64) & 1)) continue;

        unsigned char scancode = inb(0x60);
        if(scancode == 0x11) move_cursor(0, -1);
        if(scancode == 0x1F) move_cursor(0, 1);
        if(scancode == 0x1E) move_cursor(-1, 0);
        if(scancode == 0x20) move_cursor(1, 0);
        if(scancode == 0x1C) drawing = 1;
        if(scancode == 0x9C) drawing = 0;
        
        if(scancode & 0x80) continue;

    }
}