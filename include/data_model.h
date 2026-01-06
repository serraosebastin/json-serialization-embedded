#ifndef DATA_MODEL_H
#define DATA_MODEL_H

/* One data point */
typedef struct {
    char timestamp[20];         // "YYYY-MM-DD HH:MM"
    char meter_datetime[20];    // "YYYY-MM-DD HH:MM"
    double total_m3;
    char status[8];             // "OK"
} DataPoint;

/* One device */
typedef struct {
    char media[16];
    char meter[16];
    char deviceId[32];
    char unit[8];

    int data_count;
    DataPoint *data;
} DeviceReading;

/* Values block */
typedef struct {
    int device_count;
    DeviceReading *readings;
} ValuesBlock;

/* Gateway-level packet */
typedef struct {
    char gatewayId[32];
    char date[11];              // YYYY-MM-DD
    char deviceType[16];
    int interval_minutes;
    int total_readings;

    ValuesBlock values;
} GatewayPacket;

#endif
