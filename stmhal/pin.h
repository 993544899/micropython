/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// This file requires pin_defs_xxx.h (which has port specific enums and
// defines, so we include it here. It should never be included directly

#include PIN_DEFS_PORT_H

typedef struct {
  mp_obj_base_t base;
  uint8_t idx;
  uint8_t fn;
  uint8_t unit;
  uint8_t type;

  union {
    void          *reg;

    PIN_DEFS_PORT_AF_UNION
  };
} pin_af_obj_t;

typedef struct {
  mp_obj_base_t base;
  const char *name;
  uint32_t port   : 4;
  uint32_t pin    : 5;      // Some ARM processors use 32 bits/PORT
  uint32_t num_af : 4;
  uint32_t adc_channel : 5; // Some ARM processors use 32 bits/PORT
  uint32_t adc_num  : 3;    // 1 bit per ADC
  uint32_t pin_mask;
  pin_gpio_t *gpio;
  const pin_af_obj_t *af;
} pin_obj_t;

extern const mp_obj_type_t pin_type;
extern const mp_obj_type_t pin_af_type;

typedef struct {
  const char *name;
  const pin_obj_t *pin;
} pin_named_pin_t;

extern const pin_named_pin_t pin_board_pins[];
extern const pin_named_pin_t pin_cpu_pins[];

//extern pin_map_obj_t pin_map_obj;

typedef struct {
    mp_obj_base_t base;
    qstr name;
    const pin_named_pin_t *named_pins;
} pin_named_pins_obj_t;

extern const pin_named_pins_obj_t pin_board_pins_obj;
extern const pin_named_pins_obj_t pin_cpu_pins_obj;

void pin_init(void);
const pin_obj_t *pin_find(mp_obj_t user_obj);
const pin_obj_t *pin_find_named_pin(const pin_named_pin_t *pins, const char *name);
const pin_af_obj_t *pin_find_af(const pin_obj_t *pin, uint8_t fn, uint8_t unit, uint8_t pin_type);
