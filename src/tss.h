/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Declaracion de estructuras para administrar tareas
*/

#ifndef __TSS_H__
#define __TSS_H__

#include "gdt.h"
#include "types.h"

typedef struct str_tss {
  uint16_t ptl;
  uint16_t unused0;
  uint32_t esp0;
  uint16_t ss0;
  uint16_t unused1;
  uint32_t esp1;
  uint16_t ss1;
  uint16_t unused2;
  uint32_t esp2;
  uint16_t ss2;
  uint16_t unused3;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint16_t es;
  uint16_t unused4;
  uint16_t cs;
  uint16_t unused5;
  uint16_t ss;
  uint16_t unused6;
  uint16_t ds;
  uint16_t unused7;
  uint16_t fs;
  uint16_t unused8;
  uint16_t gs;
  uint16_t unused9;
  uint16_t ldt;
  uint16_t unused10;
  uint16_t dtrap;
  uint16_t iomap;
} __attribute__((__packed__, aligned(8))) tss_t;

extern tss_t tss_initial;
extern tss_t tss_idle;

extern tss_t tss_rick;
extern tss_t tss_rick_MrMs0;
extern tss_t tss_rick_MrMs1;
extern tss_t tss_rick_MrMs2;
extern tss_t tss_rick_MrMs3;
extern tss_t tss_rick_MrMs4;
extern tss_t tss_rick_MrMs5;
extern tss_t tss_rick_MrMs6;
extern tss_t tss_rick_MrMs7;
extern tss_t tss_rick_MrMs8;
extern tss_t tss_rick_MrMs9;

extern tss_t tss_morty;
extern tss_t tss_morty_MrMs0;
extern tss_t tss_morty_MrMs1;
extern tss_t tss_morty_MrMs2;
extern tss_t tss_morty_MrMs3;
extern tss_t tss_morty_MrMs4;
extern tss_t tss_morty_MrMs5;
extern tss_t tss_morty_MrMs6;
extern tss_t tss_morty_MrMs7;
extern tss_t tss_morty_MrMs8;
extern tss_t tss_morty_MrMs9;

void tss_init(void);
void task_init(tss_t* new_tss,paddr_t phy_task, vaddr_t virt_task, paddr_t task_code, size_t pages);
void task_init_mr_meeseek(tss_t *new_tss, uint32_t cr3, paddr_t phy_task, vaddr_t virt_task, paddr_t task_code, uint32_t pila_0);
void tss_init_idle(void);
void tss_init_gdt(void);

typedef struct str_MrMs {
  uint8_t in_use;
  tss_t task_seg;
}tss_mrms;

extern tss_mrms tss_Mortymrms[10];
extern tss_mrms tss_Rickmrms[10];

#endif //  __TSS_H__
