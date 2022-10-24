
void sys_read(char * buff, int length);
void sys_write(int x, int y, char*  c, int len, int fd);
void sys_draw_rectangle(int x, int y, int width, int height, int color);
void sys_clear_screen();
void sys_write_char(int x, int y, char c, int fd);
void sys_get_seconds(int * sec);
void sys_get_minutes(int * min);
void sys_get_hours(int * hours);
void sys_change_font_size(int size);