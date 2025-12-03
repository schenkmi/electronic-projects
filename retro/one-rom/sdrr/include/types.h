// Contains types

// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

#ifndef TYPES_H
#define TYPES_H

// Blink patterns for limp mode
typedef enum limp_mode_pattern {
    LIMP_MODE_NONE = 0,
    LIMP_MODE_NO_ROMS = 1,
    LIMP_MODE_INVALID_CONFIG = 2,
} limp_mode_pattern_t;

#endif // TYPES_H
