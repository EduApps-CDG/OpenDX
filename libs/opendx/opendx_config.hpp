#pragma once

#include <string>

#define CONFIG_OPTION(name, val) \
    name: new OpenDX_ConfigOption{#name, val}

struct OpenDX_ConfigOption {
    std::string name;
    std::string value;
};

/// @brief OpenDX configuration options from the opendx.conf file
struct OpenDX_Config {
    /// @brief the preferred graphics card set by configuration
    OpenDX_ConfigOption preferred_card;
    /// @brief  Experimental: ensure that our fb is the "master" framebuffer (the fb that owns the display)
    OpenDX_ConfigOption experimental_force_master;
} OpenDX_Config;