#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>
#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */
/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */



DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas LA TABLA

static void setup_IDT_entry (int index, uint64_t offset); // index es EN QUE POSICION offset puntero a funcccc

void load_idt() { // la llamo al principio del main para que me cargue la idt 
  _cli();
  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);
  setup_IDT_entry(0x21,  &_irq01Handler); // agrego el teclado!!! SI LE AGREGO EL CASTEO DE LOS ANTERIORES SE ME ROMPE QUE ONDAAAAA LOCO
  setup_IDT_entry(0x80,&_sysCallHandler);
	//Solo interrupcion timer tick habilitadas CAMBIARLA PARA LA DEL TECLADO (ABRIR EL CORRESPONDIENTE IRQ 1)
	picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}