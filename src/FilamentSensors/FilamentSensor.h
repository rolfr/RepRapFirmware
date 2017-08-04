/*
 * FilamentSensor.h
 *
 *  Created on: 20 Jul 2017
 *      Author: David
 */

#ifndef SRC_FILAMENTSENSORS_FILAMENTSENSOR_H_
#define SRC_FILAMENTSENSORS_FILAMENTSENSOR_H_

#include "RepRapFirmware.h"
#include "MessageType.h"

class FilamentSensor
{
public:
	// Configure this sensor returning true if error
	virtual bool Configure(GCodeBuffer& gb, StringRef& reply, bool& seen) = 0;

	// Call the following regularly to keep the status up to date
	virtual void Poll() = 0;

	// Call the following at intervals to check the status. This is only called when extrusion is in progress or imminent.
	// 'filamentConsumed' is the net amount of extrusion since the last call to this function.
	// Return nullptr if everything is OK, else an error message.
	virtual const char *Check(float filamentConsumed) = 0;

	// Print diagnostic info for this sensor
	virtual void Diagnostics(MessageType mtype, unsigned int extruder) = 0;

	// ISR for when the pin state changes
	virtual void Interrupt() = 0;

	// Override the virtual destructor if your derived class allocates any dynamic memory
	virtual ~FilamentSensor();

	// Return the type of this sensor
	int GetType() const { return type; }

	// Create a filament sensor returning null if not a valid sensor type
	static FilamentSensor *Create(int type);

protected:
	FilamentSensor(int t) : type(t), pin(NoPin) { }

	bool ConfigurePin(GCodeBuffer& gb, StringRef& reply, bool& seen);

	int GetEndstopNumber() const { return endstopNumber; }

	Pin GetPin() const { return pin; }

private:
	static void InterruptEntry(void *param);

	int type;
	int endstopNumber;
	Pin pin;
};

#endif /* SRC_FILAMENTSENSORS_FILAMENTSENSOR_H_ */
