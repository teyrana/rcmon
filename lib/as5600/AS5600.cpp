/// \file AS56000.cpp
///

#include "pico/stdlib.h"
#include "pico/binary_info.h"


#include "AS5600.h"

AS5600::AS5600(){
    bus = i2c_default;
    i2c_init(bus, 100 * 1000);

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // Make the I2C pins available to picotool diagnostics
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
}


// //  CONFIGURATION
// ====== ====== ====== ====== ====== ======
bool AS5600::configure(uint16_t value){
    if (value > 0x3FFF)
        return false;

    // writeReg2(AS5600_MEMORY_ADDRESS_CONFIGURE_LOW, value);
    // return true;

    // DEBUG
    return false;
}

bool AS5600::good() const {

    // bool AS5600::isConnected()
    // {
    //   _wire->beginTransmission(_address);
    //   return ( _wire->endTransmission() == 0);
    // }

    return true;
}

// uint8_t AS5600::readReg(uint8_t reg)
// {
//   _error = AS5600_OK;
//   _wire->beginTransmission(_address);
//   _wire->write(reg);

//   uint8_t n = _wire->requestFrom(_address, (uint8_t)1);

//   uint8_t _data = _wire->read();
//   return _data;
// }


// uint16_t AS5600::readReg2(uint8_t reg)
// {
//   _error = AS5600_OK;
//   _wire->beginTransmission(_address);
//   _wire->write(reg);
//   if (_wire->endTransmission() != 0)
//   {
//     _error = AS5600_ERROR_I2C_READ_2;
//  


bool AS5600::read( uint8_t register_address ){
    write_buffer[0] = register_address;
    write_buffer[1] = 0;
    write_buffer[2] = 0;
    write_buffer[3] = 0;
    const size_t write_count = 1;

    // DEBUG
    // printf("    >>%02x %02x %02x %02x \n", 
    //         write_buffer[0], write_buffer[1], write_buffer[2], write_buffer[3]);

    i2c_write_blocking(i2c_default, i2c_addr, write_buffer.data(), write_count, true);

    const int read_ok = i2c_read_blocking(bus, i2c_addr, read_buffer.data(), read_buffer.size(), false);

    if( PICO_ERROR_GENERIC == read_ok ){
        printf("    ::read-error-generic: %d \n", read_ok );
        return false;
    }else if( read_ok < 0 ){
        printf("    ::read-error-other: %d \n", read_ok );
        return false;
    }

    // // DEBUG
    // printf("    << [read-ok] %02x %02x %02x %02x  %02x %02x %02x %02x\n",
    //         read_buffer[0], read_buffer[1], read_buffer[2], read_buffer[3],
    //         read_buffer[1], read_buffer[2], read_buffer[3], read_buffer[4]);
    
    return true;
}

uint16_t AS5600::read_config(){
    const int read_ok = read(AS5600_REGISTER_ADDRESS_CONFIGURE_LOW);

    if( 0 < read_ok ){
        return ((read_buffer[0]<<8) + read_buffer[1]) & 0x3FFF;
    }

    return 0;
}

uint16_t AS5600::read_raw_angle(){
    const int read_ok = read(AS5600_REGISTER_ADDRESS_RAW_ANGLE);

    if( 0 < read_ok ){
        return ((read_buffer[0]<<8) + read_buffer[1]) & 0x0FFF;
    }

    return 0;
}

uint16_t AS5600::read_scale_angle(){
    const int read_ok = read(AS5600_REGISTER_ADDRESS_SCALE_ANGLE);

    if( 0 < read_ok ){
        return ((read_buffer[0]<<8) + read_buffer[1]) & 0x0FFF;
    }

    return 0;
}

uint8_t AS5600::read_status(){
   const int read_ok = read(AS5600_REGISTER_ADDRESS_STATUS);

    if( 0 < read_ok ){
        return read_buffer[0];
    }

    return 0;
}


int AS5600::write( uint8_t mem_addr, uint8_t data ){
    write_buffer[0] = mem_addr;
    write_buffer[1] = data;
    const size_t write_count = 2;

    auto write_ok = i2c_write_blocking( bus, i2c_addr, write_buffer.data(), write_count, false);
    return write_ok;
}



// /////////////////////////////////////////////////////////
// //
// //  CONFIGURATION REGISTERS + direction pin
// //
// void AS5600::setDirection(uint8_t direction)
// {
//   _direction = direction;
//   if (_directionPin != AS5600_SW_DIRECTION_PIN)
//   {
//     digitalWrite(_directionPin, _direction);
//   }
// }


// uint8_t AS5600::getDirection()
// {
//   if (_directionPin != AS5600_SW_DIRECTION_PIN)
//   {
//     _direction = digitalRead(_directionPin);
//   }
//   return _direction;
// }


// uint8_t AS5600::getZMCO()
// {
//   uint8_t value = readReg(AS5600_ZMCO);
//   return value;
// }


// bool AS5600::setZPosition(uint16_t value)
// {
//   if (value > 0x0FFF) return false;
//   writeReg2(AS5600_ZPOS, value);
//   return true;
// }


// uint16_t AS5600::getZPosition()
// {
//   uint16_t value = readReg2(AS5600_ZPOS) & 0x0FFF;
//   return value;
// }


// bool AS5600::setMPosition(uint16_t value)
// {
//   if (value > 0x0FFF) return false;
//   writeReg2(AS5600_MPOS, value);
//   return true;
// }


// uint16_t AS5600::getMPosition()
// {
//   uint16_t value = readReg2(AS5600_MPOS) & 0x0FFF;
//   return value;
// }


// bool AS5600::setMaxAngle(uint16_t value)
// {
//   if (value > 0x0FFF) return false;
//   writeReg2(AS5600_MANG, value);
//   return true;
// }


// uint16_t AS5600::getMaxAngle()
// {
//   uint16_t value = readReg2(AS5600_MANG) & 0x0FFF;
//   return value;
// }



// //  details configure
// bool AS5600::setPowerMode(uint8_t powerMode)
// {
//   if (powerMode > 3) return false;
//   uint8_t value = readReg(AS5600_CONF + 1);
//   value &= ~AS5600_CONF_POWER_MODE;
//   value |= powerMode;
//   writeReg(AS5600_CONF + 1, value);
//   return true;
// }


// uint8_t AS5600::getPowerMode()
// {
//   return readReg(AS5600_CONF + 1) & 0x03;
// }


// bool AS5600::setHysteresis(uint8_t hysteresis)
// {
//   if (hysteresis > 3) return false;
//   uint8_t value = readReg(AS5600_CONF + 1);
//   value &= ~AS5600_CONF_HYSTERESIS;
//   value |= (hysteresis << 2);
//   writeReg(AS5600_CONF + 1, value);
//   return true;
// }


// uint8_t AS5600::getHysteresis()
// {
//   return (readReg(AS5600_CONF + 1) >> 2) & 0x03;
// }


// bool AS5600::setOutputMode(uint8_t outputMode)
// {
//   if (outputMode > 2) return false;
//   uint8_t value = readReg(AS5600_CONF + 1);
//   value &= ~AS5600_CONF_OUTPUT_MODE;
//   value |= (outputMode << 4);
//   writeReg(AS5600_CONF + 1, value);
//   return true;
// }


// uint8_t AS5600::getOutputMode()
// {
//   return (readReg(AS5600_CONF + 1) >> 4) & 0x03;
// }


// bool AS5600::setPWMFrequency(uint8_t pwmFreq)
// {
//   if (pwmFreq > 3) return false;
//   uint8_t value = readReg(AS5600_CONF + 1);
//   value &= ~AS5600_CONF_PWM_FREQUENCY;
//   value |= (pwmFreq << 6);
//   writeReg(AS5600_CONF + 1, value);
//   return true;
// }


// uint8_t AS5600::getPWMFrequency()
// {
//   return (readReg(AS5600_CONF + 1) >> 6) & 0x03;
// }


// bool AS5600::setSlowFilter(uint8_t mask)
// {
//   if (mask > 3) return false;
//   uint8_t value = readReg(AS5600_CONF);
//   value &= ~AS5600_CONF_SLOW_FILTER;
//   value |= mask;
//   writeReg(AS5600_CONF, value);
//   return true;
// }


// uint8_t AS5600::getSlowFilter()
// {
//   return readReg(AS5600_CONF) & 0x03;
// }


// bool AS5600::setFastFilter(uint8_t mask)
// {
//   if (mask > 7) return false;
//   uint8_t value = readReg(AS5600_CONF);
//   value &= ~AS5600_CONF_FAST_FILTER;
//   value |= (mask << 2);
//   writeReg(AS5600_CONF, value);
//   return true;
// }


// uint8_t AS5600::getFastFilter()
// {
//   return (readReg(AS5600_CONF) >> 2) & 0x07;
// }


// bool AS5600::setWatchDog(uint8_t mask)
// {
//   if (mask > 1) return false;
//   uint8_t value = readReg(AS5600_CONF);
//   value &= ~AS5600_CONF_WATCH_DOG;
//   value |= (mask << 5);
//   writeReg(AS5600_CONF, value);
//   return true;
// }


// uint8_t AS5600::getWatchDog()
// {
//   return (readReg(AS5600_CONF) >> 5) & 0x01;
// }


// /////////////////////////////////////////////////////////
// //
// //  OUTPUT REGISTERS
// //
// uint16_t AS5600::rawAngle()
// {
//   int16_t value = readReg2(AS5600_RAW_ANGLE) & 0x0FFF;
//   if (_offset > 0) value = (value + _offset) & 0x0FFF;

//   if ((_directionPin == AS5600_SW_DIRECTION_PIN) &&
//       (_direction == AS5600_COUNTERCLOCK_WISE))
//   {
//     value = (4096 - value) & 0x0FFF;
//   }
//   return value;
// }


// uint16_t AS5600::readAngle()
// {
//   uint16_t value = readReg2(AS5600_ANGLE) & 0x0FFF;
//   if (_offset > 0) value = (value + _offset) & 0x0FFF;

//   if ((_directionPin == AS5600_SW_DIRECTION_PIN) &&
//       (_direction == AS5600_COUNTERCLOCK_WISE))
//   {
//     value = (4096 - value) & 0x0FFF;
//   }
//   return value;
// }


// bool AS5600::setOffset(float degrees)
// {
//   //  expect loss of precision.
//   if (abs(degrees) > 36000) return false;
//   bool neg = (degrees < 0);
//   if (neg) degrees = -degrees;

//   uint16_t offset = round(degrees * AS5600_DEGREES_TO_RAW);
//   offset &= 4095;
//   if (neg) offset = 4096 - offset;
//   _offset = offset;
//   return true;
// }


// float AS5600::getOffset()
// {
//   return _offset * AS5600_RAW_TO_DEGREES;
// }


// bool AS5600::increaseOffset(float degrees)
// {
//   //  add offset to existing offset in degrees.
//   return setOffset((_offset * AS5600_RAW_TO_DEGREES) + degrees);
// }


// /////////////////////////////////////////////////////////
// //
// //  STATUS REGISTERS
// //
// uint8_t AS5600::readStatus()
// {
//   uint8_t value = readReg(AS5600_STATUS);
//   return value;
// }


// uint8_t AS5600::readAGC()
// {
//   uint8_t value = readReg(AS5600_AGC);
//   return value;
// }


// uint16_t AS5600::readMagnitude()
// {
//   uint16_t value = readReg2(AS5600_MAGNITUDE) & 0x0FFF;
//   return value;
// }


// bool AS5600::detectMagnet()
// {
//   return (readStatus() & AS5600_MAGNET_DETECT) > 1;
// }


// bool AS5600::magnetTooStrong()
// {
//   return (readStatus() & AS5600_MAGNET_HIGH) > 1;
// }


// bool AS5600::magnetTooWeak()
// {
//   return (readStatus() & AS5600_MAGNET_LOW) > 1;
// }


// /////////////////////////////////////////////////////////
// //
// //  BURN COMMANDS
// //
// //  DO NOT UNCOMMENT - USE AT OWN RISK - READ DATASHEET
// //
// //  void AS5600::burnAngle()
// //  {
// //    writeReg(AS5600_BURN, x0x80);
// //  }
// //
// //
// //  See https://github.com/RobTillaart/AS5600/issues/38
// //  void AS5600::burnSetting()
// //  {
// //    writeReg(AS5600_BURN, 0x40);
// //    delay(5);
// //    writeReg(AS5600_BURN, 0x01);
// //    writeReg(AS5600_BURN, 0x11);
// //    writeReg(AS5600_BURN, 0x10);
// //    delay(5);
// //  }


// float AS5600::getAngularSpeed(uint8_t mode)
// {
//   uint32_t now     = micros();
//   int      angle   = readAngle();
//   uint32_t deltaT  = now - _lastMeasurement;
//   int      deltaA  = angle - _lastAngle;

//   //  assumption is that there is no more than 180° rotation
//   //  between two consecutive measurements.
//   //  => at least two measurements per rotation (preferred 4).
//   if (deltaA >  2048) deltaA -= 4096;
//   if (deltaA < -2048) deltaA += 4096;
//   float    speed   = (deltaA * 1e6) / deltaT;

//   //  remember last time & angle
//   _lastMeasurement = now;
//   _lastAngle       = angle;

//   //  return radians, RPM or degrees.
//   if (mode == AS5600_MODE_RADIANS)
//   {
//     return speed * AS5600_RAW_TO_RADIANS;
//   }
//   if (mode == AS5600_MODE_RPM)
//   {
//     return speed * AS5600_RAW_TO_RPM;
//   }
//   //  default return degrees
//   return speed * AS5600_RAW_TO_DEGREES;
// }


// /////////////////////////////////////////////////////////
// //
// //  POSITION cumulative
// //
// int32_t AS5600::getCumulativePosition()
// {
//   int16_t value = readReg2(AS5600_ANGLE) & 0x0FFF;
//   if (_error != AS5600_OK) return _position;

//   //  whole rotation CW?
//   //  less than half a circle
//   if ((_lastPosition > 2048) && ( value < (_lastPosition - 2048)))
//   {
//     _position = _position + 4096 - _lastPosition + value;
//   }
//   //  whole rotation CCW?
//   //  less than half a circle
//   else if ((value > 2048) && ( _lastPosition < (value - 2048)))
//   {
//     _position = _position - 4096 - _lastPosition + value;
//   }
//   else _position = _position - _lastPosition + value;
//   _lastPosition = value;

//   return _position;
// }


// int32_t AS5600::getRevolutions()
// {
//   int32_t p = _position >> 12;  //  divide by 4096
//   return p;
//   // if (p < 0) p++;
//   // return p;
// }


// int32_t AS5600::resetPosition(int32_t position)
// {
//   int32_t old = _position;
//   _position = position;
//   return old;
// }


// int32_t AS5600::resetCumulativePosition(int32_t position)
// {
//   _lastPosition = readReg2(AS5600_RAW_ANGLE) & 0x0FFF;
//   int32_t old = _position;
//   _position = position;
//   return old;
// }


// int AS5600::lastError()
// {
//   int value = _error;
//   _error = AS5600_OK;
//   return value;
// }



// /////////////////////////////////////////////////////////////////////////////
// //
// //  AS5600L
// //
// AS5600L::AS5600L(uint8_t address, TwoWire *wire) : AS5600(wire)
// {
//   _address = address;;   //  0x40 = default address AS5600L.
// }


// bool AS5600L::setAddress(uint8_t address)
// {
//   //  skip reserved I2C addresses
//   if ((address < 8) || (address > 119)) return false;

//   //  note address need to be shifted 1 bit.
//   writeReg(AS5600_I2CADDR, address << 1);
//   writeReg(AS5600_I2CUPDT, address << 1);

//   //  remember new address.
//   _address = address;
//   return true;
// }


// bool AS5600L::setI2CUPDT(uint8_t address)
// {
//   //  skip reserved I2C addresses
//   if ((address < 8) || (address > 119)) return false;
//   writeReg(AS5600_I2CUPDT, address << 1);
//   return true;
// }


// uint8_t AS5600L::getI2CUPDT()
// {
//   return (readReg(AS5600_I2CUPDT) >> 1);
// }


// //  -- END OF FILE --


