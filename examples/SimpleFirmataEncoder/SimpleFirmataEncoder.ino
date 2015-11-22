/*
  Copyright (C) 2014 Nicolas Panel. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
 */

#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
#include <FirmataReporting.h>
#include <Encoder.h>
#include "FirmataEncoder.h"

FirmataExt firmataExt;
FirmataReporting reporting;
FirmataEncoder encoder;

/*==============================================================================
 * FUNCTIONS
 *============================================================================*/
void systemResetCallback()
{
  firmataExt.reset();
}

/*==============================================================================
 * SETUP()
 *============================================================================*/
void setup()
{
  // TODO - pass the version of this firmware rather than the Firmata protocol
  // version. Making that change now however may break compatibility.
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);
  firmataExt.addFeature(reporting);
  firmataExt.addFeature(encoder);
  /* systemResetCallback is declared here (in ConfigurableFirmata.ino) */
  Firmata.attach(SYSTEM_RESET, systemResetCallback);
  Firmata.begin(57600);
  systemResetCallback();  // reset to default config
}

/*==============================================================================
 * LOOP()
 *============================================================================*/
void loop()
{
  /* STREAMREAD - processing incoming messagse as soon as possible, while still
   * checking digital inputs.  */
  while (Firmata.available()) {
    Firmata.processInput();
  }

  if (reporting.elapsed()) {
    encoder.report();
  }
}
