/**
 * @file SHAGEE_print.h
 * @author MASA SHAGEE '23-'24 season
 * @brief This is a serial wire debug printer for STLink V3. Made for an STM32F722RE on Arduino through PlatformIO
 * @version 0.1
 * @date 2024-04-11
 */

/* 
* This is old info, pls ignore:
* The methodology of how this works can be found here: https://www.codeinsideout.com/blog/stm32/swv/
* As the tutorial states, the following code should be added in the top of main to make this work:

// Enable TRCENA
DEMCR |= ( 1 << 24);
// Enable stimulus port 0
ITM_TRACE_EN |= ( 1 << 0);

*/

/*
* Three different methods for printing via SWO:
* s.printf("Hello world! %d\n", myInt), print_swo("Looping\n", 8), printf("Testing printf")
* 90% certain that this only works because we included SWOStream. That library seems to do all the setup
*/


// header guard
#ifndef SHAGEE_PRINT
#define SHAGEE_PRINT

#include <SWOStream.h>

extern SWOStream s(2000); // 2000

// C++ guard
#ifdef __cplusplus
extern "C" {
#endif

/* Override low-level _write system call */
int _write(int file, char *ptr, int len) {
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        ITM_SendChar(*ptr++);
    }
    return len;
}

void print_swo(const char *data, const uint32_t size)
{
    uint32_t i;
    for(i = 0; i<size; i++)
    {
        ITM_SendChar(data[i]);
    }
}

int __io_putchar(int ch){
	ITM_SendChar(ch);
	return ch;
}

#ifdef __cplusplus // end of C++ guard
}
#endif

#endif // end of SHAGEE_PRINT header guard
