#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <imgui.h>
#include <stb_image.h>
#include "setup/D3D11Device.h"

std::unordered_map<std::string, ID3D11ShaderResourceView*> TextureManager::textures;

bool TextureManager::LoadFromMemory(const std::string &key, const unsigned char *fileData, size_t dataSize) {
    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory(
        fileData,
        dataSize,
        &width,
        &height,
        &channels,
        DEFAULT_CHANNEL_COUNT
    );

    if (!pixels) { return false; }

    const D3D11_TEXTURE2D_DESC desc = CreateDefaultTexture2D(width, height);

    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = pixels;
    subResource.SysMemPitch = width * DEFAULT_CHANNEL_COUNT;

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = D3D11Device::g_pd3dDevice->CreateTexture2D(&desc, &subResource, &texture);
    if (FAILED(hr)) {
        stbi_image_free(pixels);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;

    ID3D11ShaderResourceView* shaderResourceView = nullptr;
    hr = D3D11Device::g_pd3dDevice->CreateShaderResourceView(texture, &srvDesc, &shaderResourceView);
    if (FAILED(hr)) {
        texture->Release();
        stbi_image_free(pixels);
        return false;
    }

    texture->Release();
    stbi_image_free(pixels);

    textures[key] = shaderResourceView;

    return true;
}

ImTextureID TextureManager::Get(const std::string &key) {
    return reinterpret_cast<ImTextureID>(textures[key]);
}

void TextureManager::ReleaseAll() {
    for (auto&[key, value] : textures) {
        if (value) {
            value->Release();
        }
    }
}
