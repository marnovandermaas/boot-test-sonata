#define CHERIOT_NO_AMBIENT_MALLOC
#define CHERIOT_NO_NEW_DELETE

#include <cheri.hh>
#include <platform-uart.hh>
#include <stdint.h>

using namespace CHERI;

#define GPIO_VALUE (0xFFFFFFFF)

//Capability<volatile uint32_t> stored_pointer;

/**
 * C++ entry point for the loader.  This is called from assembly, with the
 * read-write root in the first argument.
 */
extern "C" uint32_t rom_loader_entry(void *rwRoot)
{
	Capability<void> root{rwRoot};
	Capability<volatile uint32_t> gpio = root.cast<volatile uint32_t>();
	gpio.address() = 0x80000000;
	gpio.bounds() = sizeof(uint32_t);

    uint32_t gpio_value = 0;
    //stored_pointer = gpio.cast<volatile uint32_t>();
	while (true) {
        gpio_value ^= GPIO_VALUE;
        for (int i = 0; i < 500000; i++) {
		    *((volatile uint32_t *) gpio) = gpio_value;
        }
	}
}
