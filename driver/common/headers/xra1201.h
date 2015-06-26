// Copyright (c) 2014, Anaren Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies, 
// either expressed or implied, of the FreeBSD Project.

#ifndef XRA1201_H
#define XRA1201_H

#include "types.h"
#include "../i2c/i2c.h"

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */
#ifndef bool
#define bool uint8
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


/**
Write a 16-bit value to a device register.  All of the XRA1201 registers are
read/write except for the GPIO State Register and Input Interrupt Status
Register.  This function does not do any form of error checking, so trying to
write to one of the read-only registers may result in undesirable behavior.
@param id device ID (0 to 31) on i2c bus
@param addr device register address
@param data data to be written to the specified register address
*/
void XRA1201_WriteReg(uint8 id, uint8 addr, uint16 data);

/**
Read a 16-bit value from a device register.
@param id device ID (0 to 31) on i2c bus
@param addr device register address
@return data read from the specified register address
*/
uint16 XRA1201_ReadReg(uint8 id, uint8 addr);

/**
Read the current state of the GPIO pins. The value will be inverted for input
pins configured for Input Polarity Inversion in the PIR register.  For pins
configured as outputs, the last value written to the OCR register will be
returned.  Calling this function clears the XRA1201 interrupt.
@param id device ID (0 to 31) on i2c bus
@return current value in the GSR register
*/
uint16 XRA1201_GetGpioState(uint8 id);

/**
Change the state of the GPIO output pins by writing to the OCR register.
@param id device ID (0 to 31) on i2c bus
@param data specifies the new state of the GPIO output pins
*/
void XRA1201_SetOutputValue(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetOutputValue() function.  The
default value following power-up is 0xFFFF.
@param id device ID (0 to 31) on i2c bus
@return current value in the OCR register
*/
uint16 XRA1201_GetOutputValue(uint8 id);

/**
Enable/disable polarity inversion on GPIO input pins.  Setting a bit to '1'
inverts the corresponding GPIO input pin value returned when reading the GSR
register.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins to invert
*/
void XRA1201_SetInputPolarityInversion(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInputPolarityInversion() function.
The default value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the PIR register
*/
uint16 XRA1201_GetInputPolarityInversion(uint8 id);

/**
Select GPIO pin direction.  Setting a bit to '0' configures the corresponding
GPIO pin as an output while setting the bit to '1' configures the GPIO pin as an
input.
@param id device ID (0 to 31) on i2c bus
@param data GPIO pin direction
*/
void XRA1201_SetPinDirection(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetPinDirection() function. The
default value following power-up is 0xFFFF.
@param id device ID (0 to 31) on i2c bus
@return current value in the GCR register
*/
uint16 XRA1201_GetPinDirection(uint8 id);

/**
Enable/disable internal pull-up resistor on GPIO input pins.  Setting a bit to
'1' enables the pull-up on the corresponding GPIO input pin.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins to pull-up internally
*/
void XRA1201_SetInputPullupEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInputPullupEnable() function.  The
default value following power-up is 0x0000 for the XRA1201 and 0xFFFF for the
XRA1201P.
@param id device ID (0 to 31) on i2c bus
@return current value in the PUR register
*/
uint16 XRA1201_GetInputPullupEnable(uint8 id);

/**
Enable/disable interrupts on GPIO input pins.  Setting a bit to '1' enables the
interrupt on the corresponding GPIO input pin.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins to configure with interrupts enabled
*/
void XRA1201_SetInterruptEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInterruptEnable() function. The
default value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the IER register
*/
uint16 XRA1201_GetInterruptEnable(uint8 id);

/**
Enable/disable tri-state mode on GPIO output pins.  Setting a bit to '1' enables
the tri-state mode on the corresponding GPIO output pin.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO output pins to configure for tri-state mode
*/
void XRA1201_SetOutputThreeStateEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetOutputThreeStateEnable() function.
The default value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the TSCR register
*/
uint16 XRA1201_GetOutputThreeStateEnable(uint8 id);

/**
Read the current status of the GPIO input pin interrupts.  A bit will be set to
'1' if an interrupt occurred on the corresponding GPIO input pin.  The default
value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the ISR register
*/
uint16 XRA1201_GetInterruptStatus(uint8 id);

/**
Enable/disable interrupts to be generated following the rising edge detection of
the GPIO input pins.  Setting a bit to '1' enables the interrupt to be generated
on the rising edge of the corresponding GPIO input pin.  See the XRA1201
datasheet for more details regarding the interrupt behavior.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins are to generate interrupts on the
rising edge
*/
void XRA1201_SetInterruptRisingEdgeEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInterruptRisingEdgeEnable()
function. The default value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the REIR register
*/
uint16 XRA1201_GetInterruptRisingEdgeEnable(uint8 id);

/**
Enable/disable interrupts to be generated following the falling edge detection
of the GPIO input pins.  Setting a bit to '1' enables the interrupt to be
generated on the falling edge of the corresponding GPIO input pin.  See the
XRA1201 datasheet for more details regarding the interrupt behavior.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins are to generate interrupts on the
falling edge
*/
void XRA1201_SetInterruptFallingEdgeEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInterruptFallingEdgeEnable()
function. The default value following power-up is 0x0000.
@param id device ID (0 to 31) on i2c bus
@return current value in the FEIR register
*/
uint16 XRA1201_GetInterruptFallingEdgeEnable(uint8 id);

/**
Enable/disable filtering on the GPIO input pins for generating interrupts.
Setting a bit to '1' enables the interrupt filter of the corresponding GPIO
input pin.  See the XRA1201 datasheet for more details regarding the interrupt
behavior.
@param id device ID (0 to 31) on i2c bus
@param data specifies which GPIO input pins to configure with interrupt filters
*/
void XRA1201_SetInterruptFilterEnable(uint8 id, uint16 data);

/**
Read the last value written by the XRA1201_SetInterruptFilterEnable() function.
The default value following power-up is 0xFFFF.
@param id device ID (0 to 31) on i2c bus
@return current value in the IFR register
*/
uint16 XRA1201_GetInterruptFilterEnable(uint8 id);


#endif  /* XRA1201_H */
