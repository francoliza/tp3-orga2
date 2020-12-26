/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "idt.h"
#include "defines.h"
#include "isr.h"
#include "screen.h"

idt_entry_t idt[255] = {0};

idt_descriptor_t IDT_DESC = {sizeof(idt) - 1, (uint32_t)&idt};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);
        ...
    }
*/


#define IDT_ENTRY(numero)                                                                          \
    idt[numero].offset_15_0 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);        \
    idt[numero].segsel = (uint16_t) (GDT_CODE_0<<3)/*SEL DE SEG DE COD*/;                          \
    idt[numero].attr = (uint16_t) 0x8E00;                                                          \
    idt[numero].offset_31_16 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF);

#define IDT_ENTRY_SYSTEM(numero)                                                                    \
    idt[numero].offset_15_0 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);         \
    idt[numero].segsel = (uint16_t) (GDT_CODE_0 << 3);                                              \
    idt[numero].attr = (uint16_t) 0xEE00;                                                           \
    idt[numero].offset_31_16 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF);




void idt_init() {
    // Excepciones
  IDT_ENTRY(0);
  IDT_ENTRY(1);
  IDT_ENTRY(2);
  IDT_ENTRY(3);
  IDT_ENTRY(4);
  IDT_ENTRY(5);
  IDT_ENTRY(6);
  IDT_ENTRY(7);
  IDT_ENTRY(8);
  IDT_ENTRY(9);
  IDT_ENTRY(10);
  IDT_ENTRY(11);
  IDT_ENTRY(12);
  IDT_ENTRY(13);
  IDT_ENTRY(14);
  IDT_ENTRY(16);
  IDT_ENTRY(17);
  IDT_ENTRY(18);
  IDT_ENTRY(19);
  IDT_ENTRY(32);
  IDT_ENTRY(33);

  IDT_ENTRY_SYSTEM(88);
  IDT_ENTRY_SYSTEM(89);
  IDT_ENTRY_SYSTEM(100);
  IDT_ENTRY_SYSTEM(123);
    
}



void rutina_de_interrupciones(int number){ // Dependiendo del número de interrupción muentra el mensaje de error en pantalla

  switch (number){
    case 0:
        print("Divide error [0]",26, 1, C_BG_RED | C_FG_WHITE);
        break;        
    case 1:
        print("Debug exception [1]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 2:
        print("NMI interrupt [2]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 3:
        print("Breakpoint [3]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 4:
        print("Overflow [4]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 5:
        print("BOUND Range Extended [5]",26, 1, C_BG_RED | C_FG_WHITE);
        break;        
    case 6:
        print("Invalid Opcode [6]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 7:
        print("Device not available",26, 1, C_BG_RED | C_FG_WHITE);
        print("(No math coprocessor) [7]",26, 2, C_BG_RED | C_FG_WHITE);
        
        break;
    case 8:
        print("Double fault [8]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 9:
        print("Coprocessor segment",26, 1, C_BG_RED | C_FG_WHITE);
        print("overrun(reserved) [9]",26, 2, C_BG_RED | C_FG_WHITE);
        break;
    case 10:
        print("Invalid TSS [10]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 11:
        print("Segment not present [11]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 12:
        print("Stack-segment fault [12]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 13:
        print("General protection [13]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 14:
        print("Page fault [14]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 16:
        print("x87 FPU floating point",26, 1, C_BG_RED | C_FG_WHITE);
        print("error (Math fault) [16]",26, 2, C_BG_RED | C_FG_WHITE);
        break;
    case 17:
        print("Alingment check [17]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 18:
        print("Machine Check [18]",26, 1, C_BG_RED | C_FG_WHITE);
        break;
    case 19:
        print("SIMD floating",26, 1, C_BG_RED | C_FG_WHITE);
        print("point-exception [19]",26, 2, C_BG_RED | C_FG_WHITE);
        break;        
    default:
        break;
  }

}

uint32_t chequeo_error_code(uint32_t number){
    if(number < 8 || number == 9 || number > 17 || number == 15 || number == 16){
      return 0;
    }
    // else
    return 1;
}
