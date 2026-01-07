#pragma once
#include "ui/minecraftuirendercontext.h"
#include "ui/minecraftuirendercontext.h"
#include "hooks/minecraftuirendercontexthook.h"
#include "shulkerenderer/colors.h"
#include "util/scache.h"


class ShulkerRenderer {
public:

    static void render(
        MinecraftUIRenderContext* ctx,
        float x, float y,
        int index,
        char colorCode);
};
