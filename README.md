Embedded JSON Serialization Library (w-M-Bus Style Data)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
1. Project Overview
This project implements an embedded-friendly C library that serializes structured smart-meter data into a predefined JSON format.
It represents a simplified data pipeline used in smart-meter and w-M-Bus systems:
Measurement data → C data structures → JSON serialization → gateway / backend interface
w-M-Bus radio communication, OMS, encryption, and real meter interaction are intentionally out of scope.
The focus is on clean software design, deterministic behavior, and correctness of JSON output.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2. Platform & Language Choice
Language: C
Platform: Windows host system using GCC (MinGW-w64) via MSYS2 MinGW64
Justification:
C is the de-facto standard for embedded firmware development
Predictable and deterministic memory usage
No hidden dynamic allocations
Easy portability to microcontrollers such as STM32 or ESP32
GCC toolchain closely matches embedded cross-compilers


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
3. Project Structure
The project is structured to clearly separate application code, public interfaces, and implementation logic.

json_project/
│
├── main.c                // Example application / demo
│
├── include/              // Public headers
│   ├── data_model.h      // Data structure definitions
│   └── json_serializer.h // Serialization API declaration
│
├── src/                  // Library implementation
│   └── json_serializer.c // JSON serialization logic
│
├── .gitignore            // Ignore build artifacts
└── README.md             // Project documentation

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
4. Data Model Description
The internal data model directly reflects the required JSON structure.

GatewayPacket
Holds gateway-level metadata such as gateway ID, date, device type, interval, and total readings.

ValuesBlock
Contains the number of devices and a list of device readings.

DeviceReading
Represents one meter device, including media type, meter type, device ID, unit, and its measurements.

DataPoint
Represents a single measurement containing:
timestamp
meter timestamp
total meter value
status
All strings use fixed-size buffers to avoid dynamic memory allocation.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
5. Public API
int serialize_to_json(
    const GatewayPacket *packet,
    char *out_buf,
    size_t buf_size
);

Description
Serializes a populated GatewayPacket structure into a JSON string.
Parameters
packet – input data structure
out_buf – caller-provided output buffer
buf_size – size of the output buffer in bytes
Return Values

0 → success
-1 → buffer too small or serialization error

The function is transport-agnostic and performs no I/O.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
6. Build & Run Instructions
Requirements

GCC (tested with MinGW-w64 via MSYS2 on Windows)

Compile
gcc main.c src/json_serializer.c -Iinclude -o test

Run
./test

The program prints the generated JSON to standard output.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
7. Example JSON Output
[
  {
    "gatewayId": "gateway_1234",
    "date": "1970-01-01",
    "deviceType": "stromleser",
    "interval_minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "waterstarm",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "1970-01-01 00:00",
              "meter_datetime": "1970-01-01 00:00",
              "total_m3": 107.752,
              "status": "OK"
            }
          ]
        }
      ]
    }
  }
]

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
8. Design Decisions
No external JSON libraries are used
Serialization is performed using snprintf with explicit buffer size checks
Fixed-size buffers are used instead of dynamic allocation
Deterministic memory usage suitable for embedded systems
JSON structure and field names strictly follow the assignment specification

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
9. Possible Extensions
Loop-based serialization for multiple devices and data points
Porting the library to STM32 or ESP32 platforms
Streaming or chunked JSON generation for very small buffers
Unit tests for buffer boundary conditions
