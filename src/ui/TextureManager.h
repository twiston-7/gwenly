#ifndef GWENLY_TEXTUREMANAGER_H
#define GWENLY_TEXTUREMANAGER_H

#include <d3d11.h>
#include <string>
#include <unordered_map>

class TextureManager {
    static std::unordered_map<std::string, ID3D11ShaderResourceView*> textures;

    static constexpr int DEFAULT_MIPMAP_LEVELS = 1;
    static constexpr int DEFAULT_ARRAYSIZE = 1;
    static constexpr int DEFAULT_SAMPLECOUNT = 1;
    static constexpr int DEFAULT_CHANNEL_COUNT = 4;

    static constexpr D3D11_TEXTURE2D_DESC CreateDefaultTexture2D(const unsigned int width, const unsigned int height) {
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = DEFAULT_MIPMAP_LEVELS;
        desc.ArraySize = DEFAULT_ARRAYSIZE;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = DEFAULT_SAMPLECOUNT;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        return desc;
    }

public:
    static bool LoadFromMemory(const std::string& key, const unsigned char* data, size_t dataSize);

    static ID3D11ShaderResourceView* Get(const std::string& key);

    static void ReleaseAll();
};

#endif //GWENLY_TEXTUREMANAGER_H