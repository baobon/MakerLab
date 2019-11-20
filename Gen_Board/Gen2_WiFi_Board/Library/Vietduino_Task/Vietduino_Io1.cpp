/*
 CapacitiveSense.h - Capacitive Sensing Library for 'duino / Wiring
 https://github.com/PaulStoffregen/CapacitiveSensor
 http://www.pjrc.com/teensy/td_libs_CapacitiveSensor.html
 http://playground.arduino.cc/Main/CapacitiveSensor
 Copyright (c) 2009 Paul Bagder
 Updates for other hardare by Paul Stoffregen, 2010-2016
 vim: set ts=4:

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
*/

// ensure this library description is only included once
#ifndef _VIETDUINO_IO_H_
#define _VIETDUINO_IO_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define NK_bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define NK_bitSet(value, bit) ((value) |= (1UL << (bit)))
#define NK_bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define NK_bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// Direct I/O through registers and bitmask (from OneWire library)
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
    #define __MAVR__ // tem
#elif defined(CORE_ESP8266_FEATURES_H)
    // #define ARDUINO_ARCH_ESP8266 // tem
#endif


#if defined(__MAVR__)
#define NK_PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define NK_PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define NK_IO_REG_TYPE uint8_t
#define NK_DIRECT_READ(base, mask)         (((*(base)) & (mask)) ? 1 : 0)
#define NK_DIRECT_MODE_INPUT(base, mask)   ((*((base)+1)) &= ~(mask), (*((base)+2)) &= ~(mask))
#define NK_DIRECT_MODE_OUTPUT(base, mask)  ((*((base)+1)) |= (mask))
#define NK_DIRECT_WRITE_LOW(base, mask)    ((*((base)+2)) &= ~(mask))
#define NK_DIRECT_WRITE_HIGH(base, mask)   ((*((base)+2)) |= (mask))
#define NK_DIRECT_MODE_PULLUP(base, p)  pinMode(p, INPUT_PULLUP) //NK_DIRECT_WRITE_HIGH(base, mask)

#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
#define NK_PIN_TO_BASEREG(pin)             (portOutputRegister(pin))
#define NK_PIN_TO_BITMASK(pin)             (1)
#define NK_IO_REG_TYPE uint8_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask)         (*((base)+512))
#define NK_DIRECT_MODE_INPUT(base, mask)   (*((base)+640) = 0)
#define NK_DIRECT_MODE_OUTPUT(base, mask)  (*((base)+640) = 1)
#define NK_DIRECT_WRITE_LOW(base, mask)    (*((base)+256) = 1)
#define NK_DIRECT_WRITE_HIGH(base, mask)   (*((base)+128) = 1)

#elif defined(__MKL26Z64__)
#define NK_PIN_TO_BASEREG(pin)             (portOutputRegister(pin))
#define NK_PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define NK_IO_REG_TYPE uint8_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask)         ((*((base)+16) & (mask)) ? 1 : 0)
#define NK_DIRECT_MODE_INPUT(base, mask)   (*((base)+20) &= ~(mask))
#define NK_DIRECT_MODE_OUTPUT(base, mask)  (*((base)+20) |= (mask))
#define NK_DIRECT_WRITE_LOW(base, mask)    (*((base)+8) = (mask))
#define NK_DIRECT_WRITE_HIGH(base, mask)   (*((base)+4) = (mask))

#elif defined(__SAM3X8E__)
#define NK_PIN_TO_BASEREG(pin)             (&(digitalPinToPort(pin)->PIO_PER))
#define NK_PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define NK_IO_REG_TYPE uint32_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask)         (((*((base)+15)) & (mask)) ? 1 : 0)
#define NK_DIRECT_MODE_INPUT(base, mask)   ((*((base)+5)) = (mask))
#define NK_DIRECT_MODE_OUTPUT(base, mask)  ((*((base)+4)) = (mask))
#define NK_DIRECT_WRITE_LOW(base, mask)    ((*((base)+13)) = (mask))
#define NK_DIRECT_WRITE_HIGH(base, mask)   ((*((base)+12)) = (mask))
#define NK_DIRECT_MODE_PULLUP(base, p)  pinMode(p, INPUT_PULLUP) //NK_DIRECT_WRITE_HIGH(base, mask)

#elif defined(__PIC32MX__)
#define NK_PIN_TO_BASEREG(pin)             (portModeRegister(digitalPinToPort(pin)))
#define NK_PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define NK_IO_REG_TYPE uint32_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask)         (((*(base+4)) & (mask)) ? 1 : 0)  //PORTX + 0x10
#define NK_DIRECT_MODE_INPUT(base, mask)   ((*(base+2)) = (mask))            //TRISXSET + 0x08
#define NK_DIRECT_MODE_OUTPUT(base, mask)  ((*(base+1)) = (mask))            //TRISXCLR + 0x04
#define NK_DIRECT_WRITE_LOW(base, mask)    ((*(base+8+1)) = (mask))          //LATXCLR  + 0x24
#define NK_DIRECT_WRITE_HIGH(base, mask)   ((*(base+8+2)) = (mask))          //LATXSET + 0x28

#elif defined(ARDUINO_ARCH_ESP8266)
#define NK_PIN_TO_BASEREG(pin) ((volatile uint32_t*) GPO)
#define NK_PIN_TO_BITMASK(pin) (1 << pin)
#define NK_IO_REG_TYPE uint32_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask) ((GPI & (mask)) ? 1 : 0) //GPIO_IN_ADDRESS
#define NK_DIRECT_MODE_INPUT(base, mask) (GPE &= ~(mask)) //GPIO_ENABLE_W1TC_ADDRESS
#define NK_DIRECT_MODE_OUTPUT(base, mask) (GPE |= (mask)) //GPIO_ENABLE_W1TS_ADDRESS
#define NK_DIRECT_WRITE_LOW(base, mask) (GPOC = (mask)) //GPIO_OUT_W1TC_ADDRESS
#define NK_DIRECT_WRITE_HIGH(base, mask) (GPOS = (mask)) //GPIO_OUT_W1TS_ADDRESS
#define NK_DIRECT_MODE_PULLUP(base, p) pinMode(p, INPUT_PULLUP)

#elif defined(__SAMD21G18A__)
// runs extremely slow/unreliable on Arduino Zero - help wanted....
#define NK_PIN_TO_BASEREG(pin)             portModeRegister(digitalPinToPort(pin))
#define NK_PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define NK_IO_REG_TYPE uint32_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, mask)         (((*((base)+8)) & (mask)) ? 1 : 0)
#define NK_DIRECT_MODE_INPUT(base, mask)   ((*((base)+1)) = (mask))
#define NK_DIRECT_MODE_OUTPUT(base, mask)  ((*((base)+2)) = (mask))
#define NK_DIRECT_WRITE_LOW(base, mask)    ((*((base)+5)) = (mask))
#define NK_DIRECT_WRITE_HIGH(base, mask)   ((*((base)+6)) = (mask))

#elif defined(RBL_NRF51822)
#define NK_PIN_TO_BASEREG(pin)             (0)
#define NK_PIN_TO_BITMASK(pin)             (pin)
#define NK_IO_REG_TYPE uint32_t
#define NK_IO_REG_ASM
#define NK_DIRECT_READ(base, pin)          nrf_gpio_pin_read(pin)
#define NK_DIRECT_WRITE_LOW(base, pin)     nrf_gpio_pin_clear(pin)
#define NK_DIRECT_WRITE_HIGH(base, pin)    nrf_gpio_pin_set(pin)
#define NK_DIRECT_MODE_INPUT(base, pin)    nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL)
#define NK_DIRECT_MODE_OUTPUT(base, pin)   nrf_gpio_cfg_output(pin)

#elif defined(__arc__)

#include "scss_registers.h"
#include "portable.h"
#include "avr/pgmspace.h"

#define GPIO_ID(pin)			(g_APinDescription[pin].ulGPIOId)
#define GPIO_TYPE(pin)			(g_APinDescription[pin].ulGPIOType)
#define GPIO_BASE(pin)			(g_APinDescription[pin].ulGPIOBase)
#define DIR_OFFSET_SS			0x01
#define DIR_OFFSET_SOC			0x04
#define EXT_PORT_OFFSET_SS		0x0A
#define EXT_PORT_OFFSET_SOC		0x50

/* GPIO registers base address */
#define NK_PIN_TO_BASEREG(pin)		((volatile uint32_t *)g_APinDescription[pin].ulGPIOBase)
#define NK_PIN_TO_BITMASK(pin)		pin
#define NK_IO_REG_TYPE				uint32_t
#define NK_IO_REG_ASM

static inline __attribute__((always_inline))
NK_IO_REG_TYPE directRead(volatile NK_IO_REG_TYPE *base, NK_IO_REG_TYPE pin)
{
    NK_IO_REG_TYPE ret;
    if (SS_GPIO == GPIO_TYPE(pin)) {
        ret = READ_ARC_REG(((NK_IO_REG_TYPE)base + EXT_PORT_OFFSET_SS));
    } else {
        ret = MMIO_REG_VAL_FROM_BASE((NK_IO_REG_TYPE)base, EXT_PORT_OFFSET_SOC);
    }
    return ((ret >> GPIO_ID(pin)) & 0x01);
}

static inline __attribute__((always_inline))
void directModeInput(volatile NK_IO_REG_TYPE *base, NK_IO_REG_TYPE pin)
{
    if (SS_GPIO == GPIO_TYPE(pin)) {
        WRITE_ARC_REG(READ_ARC_REG((((NK_IO_REG_TYPE)base) + DIR_OFFSET_SS)) & ~(0x01 << GPIO_ID(pin)),
                        ((NK_IO_REG_TYPE)(base) + DIR_OFFSET_SS));
    } else {
        MMIO_REG_VAL_FROM_BASE((NK_IO_REG_TYPE)base, DIR_OFFSET_SOC) &= ~(0x01 << GPIO_ID(pin));
    }
}

static inline __attribute__((always_inline))
void directModeOutput(volatile NK_IO_REG_TYPE *base, NK_IO_REG_TYPE pin)
{
    if (SS_GPIO == GPIO_TYPE(pin)) {
        WRITE_ARC_REG(READ_ARC_REG(((NK_IO_REG_TYPE)(base) + DIR_OFFSET_SS)) | (0x01 << GPIO_ID(pin)),
                        ((NK_IO_REG_TYPE)(base) + DIR_OFFSET_SS));
    } else {
        MMIO_REG_VAL_FROM_BASE((NK_IO_REG_TYPE)base, DIR_OFFSET_SOC) |= (0x01 << GPIO_ID(pin));
    }
}

static inline __attribute__((always_inline))
void directWriteLow(volatile NK_IO_REG_TYPE *base, NK_IO_REG_TYPE pin)
{
    if (SS_GPIO == GPIO_TYPE(pin)) {
        WRITE_ARC_REG(READ_ARC_REG(base) & ~(0x01 << GPIO_ID(pin)), base);
    } else {
        MMIO_REG_VAL(base) &= ~(0x01 << GPIO_ID(pin));
    }
}

static inline __attribute__((always_inline))
void directWriteHigh(volatile NK_IO_REG_TYPE *base, NK_IO_REG_TYPE pin)
{
    if (SS_GPIO == GPIO_TYPE(pin)) {
        WRITE_ARC_REG(READ_ARC_REG(base) | (0x01 << GPIO_ID(pin)), base);
    } else {
        MMIO_REG_VAL(base) |= (0x01 << GPIO_ID(pin));
    }
}

#define NK_DIRECT_READ(base, pin)		directRead(base, pin)
#define NK_DIRECT_MODE_INPUT(base, pin)	directModeInput(base, pin)
#define NK_DIRECT_MODE_OUTPUT(base, pin)	directModeOutput(base, pin)
#define NK_DIRECT_WRITE_LOW(base, pin)	directWriteLow(base, pin)
#define NK_DIRECT_WRITE_HIGH(base, pin)	directWriteHigh(base, pin)

#endif

// some 3.3V chips with 5V tolerant pins need this workaround
//
#if defined(__MK20DX256__)
#define FIVE_VOLT_TOLERANCE_WORKAROUND
#endif

//// library interface description
//class CapacitiveSensor
//{
//  // user-accessible "public" interface
//  public:
//  // methods
//	CapacitiveSensor(uint8_t sendPin, uint8_t receivePin);
//	long capacitiveSensorRaw(uint8_t samples);
//	long capacitiveSensor(uint8_t samples);
//	void set_CS_Timeout_Millis(unsigned long timeout_millis);
//	void reset_CS_AutoCal();
//	void set_CS_AutocaL_Millis(unsigned long autoCal_millis);
//  // library-accessible "private" interface
//  private:
//  // variables
//	int error;
//	unsigned long  leastTotal;
//	unsigned int   loopTimingFactor;
//	unsigned long  CS_Timeout_Millis;
//	unsigned long  CS_AutocaL_Millis;
//	unsigned long  lastCal;
//	unsigned long  total;
//	NK_IO_REG_TYPE sBit;   // send pin's ports and bitmask
//	volatile NK_IO_REG_TYPE *sReg;
//	NK_IO_REG_TYPE rBit;    // receive pin's ports and bitmask
//	volatile NK_IO_REG_TYPE *rReg;
//  // methods
//	int SenseOneCycle(void);
//};

#endif
