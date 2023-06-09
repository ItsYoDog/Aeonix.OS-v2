#include <stdio.h>

#include <stdarg.h>
#include <screen.h>

void printf(char * format, ...) {
    va_list ap;
    va_start(ap, format);

    char * ptr = format;

    while ( * ptr) {
        if ( * ptr == '%') {
            ptr++;
            char * buf;
            switch ( * ptr++) {
            case 's':
                kprintf(va_arg(ap, char * ));
                break;
            case 'd':
                kprintf(itoa(va_arg(ap, char * ), buf, 10));
                break;
            case 'x':
                kprintf(itoa(va_arg(ap, char * ), buf, 16));
                break;
            }
        } else {
            kprintc( * ptr++);
        }
    }

    va_end(ap);
}

int puts(const char *s) {
	printf(s);
	printf("\n");
	return 0;
}