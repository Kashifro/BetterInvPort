#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

#pragma pack(push, 4)
struct RectangleArea {
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct NinesliceInfo {
    float left;
    float right;
    float top;
    float bottom;
};
#pragma pack(pop)


namespace mce {
    struct Color { float r, g, b, a; };

    class TexturePtr {
    public:
        void* texture;
        void* resourceLocation;
    };
}

namespace ui {
    enum class TextAlignment : uint8_t {
        Left,
        Right,
        Center
    };
}

#pragma pack(push, 4)
struct TextMeasureData {
    float fontSize;
    float linePadding;
    bool  renderShadow;
    bool  showColorSymbol;
    bool  hideHyphen;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct CaretMeasureData {
    int  position;
    bool shouldRender;
};
#pragma pack(pop)

struct ComponentRenderBatch;
struct MinecraftUIMeasureStrategy;
class Font;
class ResourceLocation;
class HashedString;
class CustomRenderComponent;
class ClientInstance;
class ScreenContext;
class UIRepository;
class FontHandle;
class UIScene;

class MinecraftUIRenderContext {


public:
    ClientInstance* mClient;                 // 0x08
    ScreenContext*  mScreenContext;          // 0x10
    std::byte       mMeasureStrategy[0x20];  // 0x18
    float           mTextAlpha;              // 0x38
    std::byte       _pad3C[4];                // 0x3C
    UIRepository*   mUIRepository;           // 0x40
    void*           mUIService1;              // 0x48
    void*           mUIService2;              // 0x50
    std::byte       _pad58[0x28];              // 0x58
    mce::TexturePtr** mTextureGroups;         // 0x80
    std::byte       _pad88[0x48];              // 0x88
    FontHandle*     mDebugFontHandle;         // 0xD0
    const UIScene*  mCurrentScene;            // 0x120

public:
    virtual ~MinecraftUIRenderContext();
    virtual float getLineLength(Font&, const std::string&, float, bool);
    virtual float getTextAlpha();
    virtual void  setTextAlpha(float);

    virtual void drawDebugText(
        const RectangleArea&,
        const std::string&,
        const mce::Color&,
        float,
        ui::TextAlignment,
        const TextMeasureData&,
        const CaretMeasureData&
    );

    virtual void drawText(
        Font&,
        const RectangleArea&,
        const std::string&,
        const mce::Color&,
        float,
        ui::TextAlignment,
        const TextMeasureData&,
        const CaretMeasureData&
    );

    virtual void flushText(float);

    virtual void drawImage(
        const mce::TexturePtr&,
        const glm::vec2&,
        const glm::vec2&,
        const glm::vec2&,
        const glm::vec2&
    );

    virtual void drawNineslice(const mce::TexturePtr&, const NinesliceInfo&);
    virtual void flushImages(const mce::Color&, float, const HashedString&);
    virtual void beginSharedMeshBatch(ComponentRenderBatch&);
    virtual void endSharedMeshBatch(ComponentRenderBatch&);
    virtual void unk_13();
    virtual void unk_14();
    virtual void drawRectangle(const RectangleArea&, const mce::Color&, float, int);
    virtual void fillRectangle(const RectangleArea&, const mce::Color&, float);
    virtual void increaseStencilRef();
    virtual void decreaseStencilRef();
    virtual void resetStencilRef();
    virtual void fillRectangleStencil(const RectangleArea&);
    virtual void enableScissorTest(const RectangleArea&);
    virtual void disableScissorTest();
    virtual void setClippingRectangle(const RectangleArea&);
    virtual void setFullClippingRectangle();
    virtual void saveCurrentClippingRectangle();
    virtual void restoreSavedClippingRectangle();
    virtual RectangleArea getFullClippingRectangle() const;
    virtual void unk_28(); 
    virtual void renderCustom(CustomRenderComponent*, int, RectangleArea&);
    virtual void unk_30();
    virtual void unk_31();
    virtual void unk_32();
    virtual void unk_33();
    virtual void unk_34();
    virtual mce::TexturePtr getUITextureInfo(const ResourceLocation&, bool);
    virtual void touchTexture(const ResourceLocation&);
    virtual MinecraftUIMeasureStrategy* getMeasureStrategy();
    virtual void snapImageSizeToGrid(glm::vec2&);
    virtual void unk_39();
    virtual void notifyImageEstimate(std::uint64_t);
};