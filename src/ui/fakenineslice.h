#pragma once
#include </usr/include/glm/glm.hpp>

struct RectangleArea;
class MinecraftUIRenderContext;

namespace mce {
    struct Color;     
    class TexturePtr;
}

namespace uiutil {

struct TextureUV {
    glm::vec2 uvPos;
    glm::vec2 uvSize;
    float width;
    float height;
};

struct ImageInfo {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 uvPos;
    glm::vec2 uvSize;
};

class NineSlice {
public:
    NineSlice(float textureWidth,
              float textureHeight,
              float borderWidth,
              float borderHeight);

    // tint
    float shadeFactor = 0.90f;
    bool  enableShadow = true;
    float shadowOffset = 3.0f;

    void draw(MinecraftUIRenderContext* ctx,
              mce::TexturePtr const& tex,
              RectangleArea const& rect,
              mce::Color const* tint = nullptr) const;

private:
    TextureUV slice(int x, int y, int w, int h) const;
    ImageInfo scale(TextureUV const& s,
                    float x, float y,
                    float w, float h) const;

    float mTexW;
    float mTexH;
    float mBorderW;
    float mBorderH;

    TextureUV mSlices[9];
};

} // namespace uiutil
