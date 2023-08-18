#if DEBUG_MODE
// serial monitor
#define MONITOR_SPEED 115200U
#define DEBUG_MODE_SERIAL_BEGIN Serial.begin(MONITOR_SPEED)
#undef MONITOR_SPEED
#define DEBUG_MODE_SERIAL_PRINT(str) Serial.print(str)
#define DEBUG_MODE_SERIAL_PRINTLN(str) Serial.println(str)
#else
#define DEBUG_MODE_SERIAL_BEGIN
#define DEBUG_MODE_SERIAL_PRINT(str)
#define DEBUG_MODE_SERIAL_PRINTLN(str)
#endif