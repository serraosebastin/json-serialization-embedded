#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>
#include "data_model.h"

int serialize_to_json(
    const GatewayPacket *packet,
    char *out_buf,
    size_t buf_size
);

#endif
