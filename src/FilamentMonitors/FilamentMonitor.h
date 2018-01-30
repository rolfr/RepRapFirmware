/*
 * FilamentSensor.h
 *
 *  Created on: 20 Jul 2017
 *      Author: David
 */

#ifndef SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_
#define SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_

#include "RepRapFirmware.h"
#include "MessageType.h"

enum class FilamentSensorStatus : uint8_t
{
	ok,
	noFilament,
	tooLittleMovement,
	tooMuchMovement,
	sensorError
};

class FilamentMonitor
{
public:
	// Configure this sensor, returning true if error and setting 'seen' if we processed any configuration parameters
	virtual bool Configure(GCodeBuffer& gb, StringRef& reply, bool& seen) = 0;

	// Call the following at intervals to check the status. This is only called when extrusion is in progress or imminent.
	// 'filamentConsumed' is the net amount of extrusion since the last call to this function.
	virtual FilamentSensorStatus Check(bool full, bool hadNonPrintingMove, bool fromIsr, float filamentConsumed) = 0;

	// Clear the measurement state - called when we are not printing a file. Return the present/not present status if available.
	virtual FilamentSensorStatus Clear(bool full) = 0;

	// Print diagnostic info for this sensor
	virtual void Diagnostics(MessageType mtype, unsigned int extruder) = 0;

	// ISR for when the pin state changes. It should return true if the ISR wants the commanded extrusion to be fetched.
	virtual bool Interrupt() = 0;

	// Override the virtual destructor if your derived class allocates any dynamic memory
	virtual ~FilamentMonitor();

	// Return the type of this sensor
	int GetType() const { return type; }

	// Return an error message corresponding to a status code
	static const char *GetErrorMessage(FilamentSensorStatus f);

	// Poll the filament sensors
	static void Spin(bool full);

	// Return the filament sensor associated with a particular extruder
	static FilamentMonitor *GetFilamentSensor(unsigned int extruder);

	// Set the filament sensor associated with a particular extruder
	static bool SetFilamentSensorType(unsigned int extruder, int newSensorType);

	// Send diagnostics info
	static void Diagnostics(MessageType mtype);

protected:
	FilamentMonitor(unsigned int extruder, int t) : extruderNumber(extruder), type(t), pin(NoPin) { }

	bool ConfigurePin(GCodeBuffer& gb, StringRef& reply, uint32_t interruptMode, bool& seen);

	int GetEndstopNumber() const { return endstopNumber; }

	Pin GetPin() const { return pin; }

private:
	// Create a filament sensor returning null if not a valid sensor type
	static FilamentMonitor *Create(unsigned int extruder, int type);

	static void InterruptEntry(CallbackParameter param);

	static FilamentMonitor *filamentSensors[MaxExtruders];

	int32_t isrExtruderStepsCommanded;
	unsigned int extruderNumber;
	int type;
	int endstopNumber;
	Pin pin;
	bool isrWasNonPrinting;
	bool haveIsrStepsCommanded;
};

#endif /* SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_ */
