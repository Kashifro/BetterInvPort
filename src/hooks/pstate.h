#pragma once
#include <cstdint>

struct PreviewItem {
    uint8_t slot;
    uint8_t number;
};

extern PreviewItem gPreviewItems[27];
extern uint8_t gPreviewCount;
