//
//  $Id: dac.h 42 2008-10-04 18:40:36Z jcw $
//  $Revision: 42 $
//  $Author: jcw $
//  $Date: 2008-10-04 14:40:36 -0400 (Sat, 04 Oct 2008) $
//  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/dac/dac.h $
//

#ifndef __DAC_H
#define __DAC_H

#include "_config_cpu_.h"

void dac_Init(void);
void dac_Finish(void);
int dac_Set(uint new_value);

#endif
