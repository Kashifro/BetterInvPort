#pragma once
#include "ui/minecraftuirendercontext.h"
#include "ui/fakenineslice.h"

class ShulkerRenderer {
public:
    static void setPanelTexture(mce::TexturePtr const& tex);

    static void render(
        MinecraftUIRenderContext* ctx,
        float x, float y,
        char colorCode);

private:
    static bool sHasPanelTex;
    static mce::TexturePtr sPanelTex;
    static uiutil::NineSlice sPanelSlice;
};
