#include <stdio.h>
#include "json_serializer.h"

int serialize_to_json(
    const GatewayPacket *packet,
    char *out_buf,
    size_t buf_size
) {
    int written = snprintf(
        out_buf,
        buf_size,
        "[{"
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%d,"
        "\"total_readings\":%d,"
        "\"values\":{"
            "\"device_count\":%d,"
            "\"readings\":[{"
                "\"media\":\"%s\","
                "\"meter\":\"%s\","
                "\"deviceId\":\"%s\","
                "\"unit\":\"%s\","
                "\"data\":[{"
                    "\"timestamp\":\"%s\","
                    "\"meter_datetime\":\"%s\","
                    "\"total_m3\":%.3f,"
                    "\"status\":\"%s\""
                "}]"
            "}]"
        "}"
        "}]",
        packet->gatewayId,
        packet->date,
        packet->deviceType,
        packet->interval_minutes,
        packet->total_readings,
        packet->values.device_count,
        packet->values.readings[0].media,
        packet->values.readings[0].meter,
        packet->values.readings[0].deviceId,
        packet->values.readings[0].unit,
        packet->values.readings[0].data[0].timestamp,
        packet->values.readings[0].data[0].meter_datetime,
        packet->values.readings[0].data[0].total_m3,
        packet->values.readings[0].data[0].status
    );

    if (written < 0 || (size_t)written >= buf_size) {
        return -1;
    }

    return 0;
}
