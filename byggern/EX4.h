


#ifndef ex4_h_
#define ex4_h_

#include "Joystick.h"
void oled_init(void);
void oled_printf(char* data, ...);
void oled_inv_printf(char* data, ...);
int oled_put_char(unsigned char);
int oled_inv_put_char(unsigned char c);
int long_string(char* data);
void PrintMenu(void);

//typedef enum{font_4x6, font_5x7, font_5x7w, font_8x8} fontname;
//void switch_font(fontname name);
void oled_goto_letter(int letterplace);

typedef struct {
	int row, col;
} oled_position_t;

//recommended functions from the assignment text
void oled_reset(void);
void oled_home(void);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_clear_line(int line);
void oled_fill_line(int line);
void oled_pos(int row, int column);





#endif /* ex4_h_ */