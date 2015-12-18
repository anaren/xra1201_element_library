/**
 *  ----------------------------------------------------------------------------
 *  Copyright (c) 2014, Anaren Microwave, Inc.
 *
 *  For more information on licensing, please see Anaren Microwave, Inc's
 *  end user software licensing agreement: EULA.txt.
 *
 *  ----------------------------------------------------------------------------
 *
 *  xra1201.h - driver interface for the Exar XRA1201 GPIO Expander.  The
 *  XRA1201 allows for up to 32 devices on a single i2c bus, therefore each
 *  function accepts a bus identifier in the range 0 - 31 to select which device
 *  is currently being accessed.  This ID is added to the device's base address
 *  of 0x10 to determine the final i2c address.
 *
 *  @version    1.0.00
 *  @date       09 Sep 2014
 *  @author     Anaren, air@anaren.com
 *
 *  assumptions
 *  ===========
 *  - The i2c driver provides the proper signaling sequences for read & write
 *    operations.
 *  - The i2c driver meets the timing requirements specified in the XRA1201
 *    datasheet.
 *
 *  file dependency
 *  ===============
 *  i2c.h : defines the i2c read & write interfaces.
 *
 *  revision history
 *  ================
 *  ver 1.0.00 : 09 Sep 2014
 *  - initial release
 */

#include "xra1201.h"

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */

#define XRA1201_SLAVE_BASE_ADDR     0x10

#define XRA1201_GSR1_REG_ADDR       0x00  // GPIO State P0-P7 (read only)
#define XRA1201_GSR2_REG_ADDR       0x01  // GPIO State P8-P15 (read only)
#define XRA1201_OCR1_REG_ADDR       0x02  // Output Control P0-P7
#define XRA1201_OCR2_REG_ADDR       0x03  // Output Control P8-P15
#define XRA1201_PIR1_REG_ADDR       0x04  // Input Polarity Inversion P0-P7
#define XRA1201_PIR2_REG_ADDR       0x05  // Input Polarity Inversion P8-P15
#define XRA1201_GCR1_REG_ADDR       0x06  // GPIO Configuration P0-P7
#define XRA1201_GCR2_REG_ADDR       0x07  // GPIO Configuration P8-P15
#define XRA1201_PUR1_REG_ADDR       0x08  // Input Internal Pull-up Enable P0-P7
#define XRA1201_PUR2_REG_ADDR       0x09  // Input Internal Pull-up Enable P8-P15
#define XRA1201_IER1_REG_ADDR       0x0A  // Input Interrupt Enable P0-P7
#define XRA1201_IER2_REG_ADDR       0x0B  // Input Interrupt Enable P8-P15
#define XRA1201_TSCR1_REG_ADDR      0x0C  // Output 3-state Control P0-P7
#define XRA1201_TSCR2_REG_ADDR      0x0D  // Output 3-state Control P8-P15
#define XRA1201_ISR1_REG_ADDR       0x0E  // Input Interrupt Status P0-P7 (read only)
#define XRA1201_ISR2_REG_ADDR       0x0F  // Input Interrupt Status P8-P15 (read only)
#define XRA1201_REIR1_REG_ADDR      0x10  // Input Rising Edge Interrupt Enable P0-P7
#define XRA1201_REIR2_REG_ADDR      0x11  // Input Rising Edge Interrupt Enable P8-P15
#define XRA1201_FEIR1_REG_ADDR      0x12  // Input Falling Edge Interrupt Enable P0-P7
#define XRA1201_FEIR2_REG_ADDR      0x13  // Input Falling Edge Interrupt Enable P8-P15
#define XRA1201_IFR1_REG_ADDR       0x14  // Input Filter Enable P0-P7
#define XRA1201_IFR2_REG_ADDR       0x15  // Input Filter Enable P8-P15

// -----------------------------------------------------------------------------
/**
 *  Global data
 */

// -----------------------------------------------------------------------------
/**
 *  Private interface
 */

// -----------------------------------------------------------------------------
/**
 *  Public interface
 */

void XRA1201_WriteReg(uint8_t id, uint8_t addr, uint16_t data)
{
  uint8_t writeBytes[2];

  writeBytes[0] = addr;
  writeBytes[1] = data;
  AIR_I2C_Write(XRA1201_SLAVE_BASE_ADDR + id, writeBytes, 2);
}

uint16_t XRA1201_ReadReg(uint8_t id, uint8_t addr)
{
  uint8_t writeBytes[1];
  uint8_t readBytes[1];

  writeBytes[0] = addr;
  AIR_I2C_ComboRead(XRA1201_SLAVE_BASE_ADDR + id, writeBytes, 1, readBytes, 1);
  return readBytes[0];
}

uint16_t XRA1201_GetGpioState(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_GSR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_GSR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetOutputValue(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_OCR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_OCR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetOutputValue(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_OCR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_OCR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInputPolarityInversion(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_PIR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_PIR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInputPolarityInversion(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_PIR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_PIR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetPinDirection(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_GCR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_GCR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetPinDirection(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_GCR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_GCR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInputPullupEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_PUR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_PUR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInputPullupEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_PUR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_PUR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInterruptEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_IER1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_IER2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInterruptEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_IER1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_IER2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetOutputThreeStateEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_TSCR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_TSCR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetOutputThreeStateEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_TSCR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_TSCR2_REG_ADDR) << 8;
  return returnValue;
}

uint16_t XRA1201_GetInterruptStatus(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_ISR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_ISR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInterruptRisingEdgeEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_REIR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_REIR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInterruptRisingEdgeEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_REIR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_REIR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInterruptFallingEdgeEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_FEIR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_FEIR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInterruptFallingEdgeEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_FEIR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_FEIR2_REG_ADDR) << 8;
  return returnValue;
}

void XRA1201_SetInterruptFilterEnable(uint8_t id, uint16_t data)
{
  XRA1201_WriteReg(id, XRA1201_IFR1_REG_ADDR, (data >> 0) & 0xFF);
  XRA1201_WriteReg(id, XRA1201_IFR2_REG_ADDR, (data >> 8) & 0xFF);
}

uint16_t XRA1201_GetInterruptFilterEnable(uint8_t id)
{
  uint16_t returnValue = XRA1201_ReadReg(id, XRA1201_IFR1_REG_ADDR);
  
  returnValue |= (uint16_t)XRA1201_ReadReg(id, XRA1201_IFR2_REG_ADDR) << 8;
  return returnValue;
}
