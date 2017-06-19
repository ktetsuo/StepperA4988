/*
 * Stepper.cpp - Arduino Stepper library for A4988 - Version 1.0.0
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

#include "Arduino.h"
#include "StepperA4988.h"

/*
 * constructor
 * Sets which wires should control the motor.
 */
StepperA4988::StepperA4988(int number_of_steps, int step_pin, int dir_pin)
  : m_number_of_steps(number_of_steps), m_step_pin(step_pin), m_dir_pin(dir_pin)
{
  m_step_delay = 100000UL;
  m_last_step_time = 0UL;
  m_step_pin_state = LOW;
  m_dir_pin_state = LOW;
  pinMode(m_step_pin, OUTPUT);
  pinMode(m_dir_pin, OUTPUT);
  digitalWrite(m_step_pin, LOW);
  digitalWrite(m_dir_pin, LOW);
}
void StepperA4988::setSpeed(long whatSpeed)
{
  m_step_delay = 60L * 1000L * 1000L / (m_number_of_steps * whatSpeed);
}
/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void StepperA4988::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  // determine direction based on whether steps_to_move is + or -:
  const uint8_t dir = steps_to_move > 0 ? HIGH : LOW;
  if(dir != m_dir_pin_state) {
    m_dir_pin_state = dir;
    // delay more than 200ns before changing direction pin
    delayMicroseconds(1);
    // output dirction pin
    digitalWrite(m_dir_pin, dir);
    // delay more than 200ns after changing direction pin
    delayMicroseconds(1);
  }
  // decrement the number of steps, moving one step each time:
  while (steps_left > 0) {
    const unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - m_last_step_time >= m_step_delay) {
      steps_left--;
      // get the timeStamp of when you stepped:
      m_last_step_time = now;
      // output step pin
      if(m_step_pin_state == LOW) {
        m_step_pin_state = HIGH;
        digitalWrite(m_step_pin, HIGH);
      } else {
        m_step_pin_state = LOW;
        digitalWrite(m_step_pin, LOW);
      }
    }
  }
}

/*
  version() returns the version of the library:
*/
int StepperA4988::version(void)
{
  return 1;
}
