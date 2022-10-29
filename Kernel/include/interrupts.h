 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <idtLoader.h>

extern void _irq00Handler(void);
extern void _irq01Handler(void);
extern void _irq02Handler(void);
extern void _irq03Handler(void);
extern void _irq04Handler(void);
extern void _irq05Handler(void);
extern void _irq10Handler(void);
extern void _irq80Handler(void);

extern void _divisionByZeroInterruption(void);
extern void _invalidOpCodeInterruption(void);

extern void _cli(void);

extern void _sti(void);

extern void _hlt(void);

extern void picMasterMask(uint8_t mask);

extern void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
extern void haltcpu(void);

#endif /* INTERRUPS_H_ */
