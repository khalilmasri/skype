#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include "my_gui.hpp"

#include <iostream>
#include <string>
#include <vector>

// client --> call ImGui context initialisation --> then initialise chat windows

// Main code
int main(int, char **)
{
    SkypeGui skype_gui;
    skype_gui.im_gui_init();
    skype_gui.window_init();

    skype_gui.done = false;
    // Run() executes the loop until 'done'
    skype_gui.run();

    skype_gui.shutdown();

    return 0;
}
