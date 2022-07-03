#ifndef LCD_H
#define LCD_H
#define EN (1<<13)
#define RS (1<<10)
#define RW (1<<12)
#define DATA (0xFF<<15)

void delay(int T);
void led_cmd(unsigned char c);
void led_data(char d);
void lcd_str(char *ch);
void lcd_init(void);
#endif
