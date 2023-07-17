/* 
 * File:   PUSH.h
 * Author: Danika Andrino
 * Comments: PULL UP botones
 * Revision history: 16/07/2023
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PUSH_H
#define	PUSH_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void IOC_INT(uint8_t a);

#endif	/* PUSH_H */

