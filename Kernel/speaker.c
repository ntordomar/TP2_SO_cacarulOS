// https://wiki.osdev.org/PC_Speaker

//Play sound using built in speaker
#include <stdint.h>
#include <time.h> 
#include <lib.h>
#include <speaker.h>
 
 void play_sound(int nFrequence) {
 	// uint32_t Div;
 	// uint8_t tmp;
 
    //     //Set the PIT to the desired frequency
 	// Div = 1193180 / nFrequence;
 	// outb(0x43, 0xb6);
 	// outb(0x42, (uint8_t) (Div) );
 	// outb(0x42, (uint8_t) (Div >> 8));
 
    //     //And play the sound using the PC speaker
 	// tmp = inb(0x61);
  	// if (tmp != (tmp | 3)) {
 	// 	outb(0x61, tmp | 3);
 	// }
	playSound(nFrequence);
}
 
//make it shutup
 void nosound() {
    // uint8_t tmp = inb(0x61) & 0xFC;

    // outb(0x61, tmp);
	stopSound();
}
 
//Make a beep
void beep(int frec) {
    play_sound(frec);
    hold(18*3); //3 segundos
    nosound();
        //set_PIT_2(old_frequency);
}
