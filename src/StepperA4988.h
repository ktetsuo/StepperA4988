/*
 * Stepper.h - Arduino Stepper library for A4988 - Version 1.0.0
 *
 * Original library        (1.0.0)   by Tetsuya K.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * Drives a bipolar stepper motor.
 * 
 * This library usage is similar to Arduino Stepper Library.
 * ref at http://www.arduino.cc/en/Reference/Stepper
 */

// ensure this library description is only included once
#ifndef StepperA4988_h
#define StepperA4988_h

// library interface description
class StepperA4988 {
  public:
    StepperA4988(int number_of_steps, int step_pin, int dir_pin);
    void setSpeed(long whatSpeed);
    void step(int steps_to_move);
    int version(void);
  private:
    const int m_number_of_steps; // total number of steps this motor can take
    const int m_step_pin;        // step pin number
    const int m_dir_pin;         // direction pin number
    unsigned long m_step_delay;    // delay between steps, in micros, based on speed
    unsigned long m_last_step_time;
    uint8_t m_step_pin_state;
    uint8_t m_dir_pin_state;
};

#endif
