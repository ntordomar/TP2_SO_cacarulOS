
void sys_read(char * buff, int length);
void sys_write(int x, int y, char*  c, int len, int color);
void sys_draw_rectangle(int x, int y, int width, int height, int color);
void sys_clear_screen();
void sys_write_char(int x, int y, char c, int color);
void sys_get_seconds(int * sec);
void sys_get_minutes(int * min);
void sys_get_hours(int * hours);
void sys_change_font_size(int size);
void sys_get_ticks(int ticks);
void sys_beep(int freq);