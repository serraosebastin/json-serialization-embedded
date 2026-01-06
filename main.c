#include <stdio.h>
#include <string.h>
#include "include/data_model.h"
#include "include/json_serializer.h"

int main(void) {
    GatewayPacket packet;
    DeviceReading devices[1];   // ONE device
    DataPoint points[1];        // ONE data point
    char json[1024];

    /* Gateway data */
    strcpy(packet.gatewayId, "gateway_1234");
    strcpy(packet.date, "1970-01-01");
    strcpy(packet.deviceType, "stromleser");
    packet.interval_minutes = 15;
    packet.total_readings = 1;

    /* Data point (THIS WAS MISSING BEFORE) */
    strcpy(points[0].timestamp, "1970-01-01 00:00");
    strcpy(points[0].meter_datetime, "1970-01-01 00:00");
    points[0].total_m3 = 107.752;
    strcpy(points[0].status, "OK");

    /* Device */
    strcpy(devices[0].media, "water");
    strcpy(devices[0].meter, "waterstarm");
    strcpy(devices[0].deviceId, "stromleser_50898527");
    strcpy(devices[0].unit, "m3");
    devices[0].data_count = 1;
    devices[0].data = points;   // attach data point

    /* Link everything */
    packet.values.device_count = 1;
    packet.values.readings = devices;

    if (serialize_to_json(&packet, json, sizeof(json)) == 0) {
        printf("%s\n", json);
    } else {
        printf("Serialization failed\n");
    }

    return 0;
}
