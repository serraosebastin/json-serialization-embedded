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
        "[\n"
        "  {\n"
        "    \"gatewayId\": \"%s\",\n"
        "    \"date\": \"%s\",\n"
        "    \"deviceType\": \"%s\",\n"
        "    \"interval_minutes\": %d,\n"
        "    \"total_readings\": %d,\n"
        "    \"values\": {\n"
        "      \"device_count\": %d,\n"
        "      \"readings\": [\n"
        "        {\n"
        "          \"media\": \"%s\",\n"
        "          \"meter\": \"%s\",\n"
        "          \"deviceId\": \"%s\",\n"
        "          \"unit\": \"%s\",\n"
        "          \"data\": [\n"
        "            {\n"
        "              \"timestamp\": \"%s\",\n"
        "              \"meter_datetime\": \"%s\",\n"
        "              \"total_m3\": %.3f,\n"
        "              \"status\": \"%s\"\n"
        "            }\n"
        "          ]\n"
        "        }\n"
        "      ]\n"
        "    }\n"
        "  }\n"
        "]",
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
