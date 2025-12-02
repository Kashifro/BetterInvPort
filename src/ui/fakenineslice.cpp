#include "fakenineslice.h"
#include "minecraftuirendercontext.h"

using namespace uiutil;

NineSlice::NineSlice(float textureWidth,
                     float textureHeight,
                     float borderWidth,
                     float borderHeight)
    : mTexW(textureWidth),
      mTexH(textureHeight),
      mBorderW(borderWidth),
      mBorderH(borderHeight){
    const int texW = (int)textureWidth;
    const int texH = (int)textureHeight;
    const int bw   = (int)borderWidth;
    const int bh   = (int)borderHeight;

    const int midW = texW - 2 * bw;
    const int midH = texH - 2 * bh;

    mSlices[0] = slice(0,        0,        bw,   bh);
    mSlices[1] = slice(bw,       0,        midW, bh);
    mSlices[2] = slice(texW-bw,  0,        bw,   bh);

    mSlices[3] = slice(0,        bh,       bw,   midH);
    mSlices[4] = slice(bw,       bh,       midW, midH);
    mSlices[5] = slice(texW-bw,  bh,       bw,   midH);

    mSlices[6] = slice(0,        texH-bh,  bw,   bh);
    mSlices[7] = slice(bw,       texH-bh,  midW, bh);
    mSlices[8] = slice(texW-bw,  texH-bh,  bw,   bh);
}

TextureUV NineSlice::slice(int x, int y, int w, int h) const {
    return {
        glm::vec2((float)x / mTexW, (float)y / mTexH),
        glm::vec2((float)w / mTexW, (float)h / mTexH),
        (float)w,
        (float)h
    };
}

ImageInfo NineSlice::scale(TextureUV const& s,
                           float x, float y,
                           float w, float h) const
{
    return {
        glm::vec2(x, y),
        glm::vec2(w, h),
        s.uvPos,
        s.uvSize
    };
}

void NineSlice::draw(MinecraftUIRenderContext* ctx,
                     mce::TexturePtr const& tex,
                     RectangleArea const& rect,
                     mce::Color const* tintPtr) const
{
    if (!ctx) return;

    const float x0 = rect._x0;
    const float y0 = rect._y0;
    const float w  = rect._x1 - rect._x0;
    const float h  = rect._y1 - rect._y0;

    const float midW = w - 2 * mBorderW;
    const float midH = h - 2 * mBorderH;

    if (midW <= 0 || midH <= 0)
        return;

    if (enableShadow) {
        RectangleArea shadow;
        shadow._x0 = x0 + shadowOffset;
        shadow._x1 = x0 + shadowOffset + w;
        shadow._y0 = y0 + shadowOffset;
        shadow._y1 = y0 + shadowOffset + h;

        mce::Color sCol{0.0f, 0.0f, 0.0f, 0.35f};
        ctx->fillRectangle(shadow, sCol, sCol.a);
    }

    mce::Color overlay{0,0,0,0};
    bool useOverlay = false;
    if (tintPtr) {
        overlay = *tintPtr;
        overlay.r *= shadeFactor;
        overlay.g *= shadeFactor;
        overlay.b *= shadeFactor;
        overlay.a *= 0.65f;
        useOverlay = true;
    }

    ImageInfo tl = scale(mSlices[0], x0,               y0,               mBorderW, mBorderH);
    ImageInfo tm = scale(mSlices[1], x0 + mBorderW,    y0,               midW,     mBorderH);
    ImageInfo tr = scale(mSlices[2], x0 + w - mBorderW,y0,               mBorderW, mBorderH);

    ImageInfo ml = scale(mSlices[3], x0,               y0 + mBorderH,    mBorderW, midH);
    ImageInfo mm = scale(mSlices[4], x0 + mBorderW,    y0 + mBorderH,    midW,     midH);
    ImageInfo mr = scale(mSlices[5], x0 + w - mBorderW,y0 + mBorderH,    mBorderW, midH);

    ImageInfo bl = scale(mSlices[6], x0,               y0 + h - mBorderH,mBorderW, mBorderH);
    ImageInfo bm = scale(mSlices[7], x0 + mBorderW,    y0 + h - mBorderH,midW,     mBorderH);
    ImageInfo br = scale(mSlices[8], x0 + w - mBorderW,y0 + h - mBorderH,mBorderW, mBorderH);

    auto drawQuad = [&](ImageInfo const& img)
    {
        ctx->drawImage(
            tex,
            &img.pos,
            &img.size,
            &img.uvPos,
            &img.uvSize
        );

        if (useOverlay) {
            RectangleArea r;
            r._x0 = img.pos.x;
            r._x1 = img.pos.x + img.size.x;
            r._y0 = img.pos.y;
            r._y1 = img.pos.y + img.size.y;
            ctx->fillRectangle(r, overlay, overlay.a);
        }
    };

    drawQuad(tl); drawQuad(tm); drawQuad(tr);
    drawQuad(ml); drawQuad(mm); drawQuad(mr);
    drawQuad(bl); drawQuad(bm); drawQuad(br);
}
