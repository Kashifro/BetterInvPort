#include "keybinds.h"
#include <dlfcn.h>
#include <stdio.h>

inline void (*_gw_add_window_creation_callback)(void *, void (*)(void *));
inline void *(*_gw_get_primary_window)();
inline void (*_gw_add_keyboard_callback)(
    void *window,
    void *user,
    bool (*callback)(void *, int, int));

bool gSP_ToggleMode = false; //useless
bool gSP_KeyDown = false;  

void SP_register_keybinds(){
    auto gw = dlopen("libmcpelauncher_gamewindow.so", 0);
    if (!gw){
        printf("[ShulkerPreview] cannot open gamewindow lib\n");
        return;
    }

    _gw_add_window_creation_callback =
        (decltype(_gw_add_window_creation_callback))
            dlsym(gw, "game_window_add_window_creation_callback");

    _gw_get_primary_window =
        (decltype(_gw_get_primary_window))
            dlsym(gw, "game_window_get_primary_window");

    _gw_add_keyboard_callback =
        (decltype(_gw_add_keyboard_callback))
            dlsym(gw, "game_window_add_keyboard_callback");

    if (!_gw_add_window_creation_callback || !_gw_get_primary_window || !_gw_add_keyboard_callback){
        printf("[ShulkerPreview] missing keybind functions\n");
        return;
    }

    _gw_add_window_creation_callback(nullptr, [](void *){
        void* window = _gw_get_primary_window();

        _gw_add_keyboard_callback( window, nullptr, [](void*, int key, int action) -> bool{

                if (key == 72){ // H
                    if (action == 0) gSP_KeyDown = true;   // press
                    if (action == 2) gSP_KeyDown = false;  // release
                }
                return false;
            }
        );

    printf("[ShulkerPreview] Keybind ready (H)\n"); });

    printf("[ShulkerPreview] Waiting for window...\n");
}
