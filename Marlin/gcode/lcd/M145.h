/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * M145: Set the heatup state for a material in the LCD menu
 *   S<material> (0=PLA, 1=ABS)
 *   H<hotend temp>
 *   B<bed temp>
 *   F<fan speed>
 */
inline void gcode_M145() {
  int8_t material = code_seen('S') ? (int8_t)code_value_int() : 0;
  if (material < 0 || material > 1) {
    SERIAL_ERROR_START;
    SERIAL_ERRORLNPGM(MSG_ERR_MATERIAL_INDEX);
  }
  else {
    int v;
    switch (material) {
      case 0:
        if (code_seen('H')) {
          v = code_value_int();
          preheatHotendTemp1 = constrain(v, EXTRUDE_MINTEMP, HEATER_0_MAXTEMP - 15);
        }
        if (code_seen('F')) {
          v = code_value_int();
          preheatFanSpeed1 = constrain(v, 0, 255);
        }
        #if TEMP_SENSOR_BED != 0
          if (code_seen('B')) {
            v = code_value_int();
            preheatBedTemp1 = constrain(v, BED_MINTEMP, BED_MAXTEMP - 15);
          }
        #endif
        break;
      case 1:
        if (code_seen('H')) {
          v = code_value_int();
          preheatHotendTemp2 = constrain(v, EXTRUDE_MINTEMP, HEATER_0_MAXTEMP - 15);
        }
        if (code_seen('F')) {
          v = code_value_int();
          preheatFanSpeed2 = constrain(v, 0, 255);
        }
        #if TEMP_SENSOR_BED != 0
          if (code_seen('B')) {
            v = code_value_int();
            preheatBedTemp2 = constrain(v, BED_MINTEMP, BED_MAXTEMP - 15);
          }
        #endif
        break;
    }
  }
}