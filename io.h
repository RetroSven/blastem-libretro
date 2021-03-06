/*
 Copyright 2013 Michael Pavone
 This file is part of BlastEm.
 BlastEm is free software distributed under the terms of the GNU General Public License version 3 or greater. See COPYING for full license text.
*/
#ifndef IO_H_
#define IO_H_
#include <stdint.h>
#include "tern.h"

enum {
	IO_GAMEPAD3,
	IO_GAMEPAD6,
	IO_MOUSE,
	IO_MENACER,
	IO_JUSTIFIER,
	IO_SEGA_MULTI,
	IO_EA_MULTI_A,
	IO_EA_MULTI_B,
	IO_SEGA_PARALLEL,
	IO_GENERIC,
	IO_NONE
};

typedef struct {
	union {
		struct {
			uint32_t timeout_cycle;
			uint16_t th_counter;
			uint16_t gamepad_num;
		} pad;
		struct {
			int data_fd;
			int listen_fd;
		} stream;
		struct {
			uint16_t last_read_x;
			uint16_t last_read_y;
			uint16_t cur_x;
			uint16_t cur_y;
			uint8_t  tr_counter;
			uint8_t  state;
		} mouse;
	} device;
	uint8_t  output;
	uint8_t  control;
	uint8_t  input[3];
	uint8_t  device_type;
} io_port;

#define GAMEPAD_TH0 0
#define GAMEPAD_TH1 1
#define GAMEPAD_EXTRA 2
#define GAMEPAD_NONE 0xF

#define IO_TH0 0
#define IO_TH1 1
#define IO_STATE 2

enum {
	IO_WRITE_PENDING,
	IO_WRITTEN,
	IO_READ_PENDING,
	IO_READ
};

void set_keybindings(io_port *ports);
void setup_io_devices(tern_node * config, io_port * ports);
void io_adjust_cycles(io_port * pad, uint32_t current_cycle, uint32_t deduction);
void io_data_write(io_port * pad, uint8_t value, uint32_t current_cycle);
uint8_t io_data_read(io_port * pad, uint32_t current_cycle);
void handle_keydown(int keycode);
void handle_keyup(int keycode);
void handle_joydown(int joystick, int button);
void handle_joyup(int joystick, int button);
void handle_joy_dpad(int joystick, int dpad, uint8_t state);
void handle_mouse_moved(int mouse, uint16_t x, uint16_t y);

#endif //IO_H_

