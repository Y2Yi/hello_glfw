//
// Created by 岳郅宇 on 2024/7/25.
//
#ifndef TEXTURE_1_H
#define TEXTURE_1_H

#include <GLFW/glfw3.h>
#include "../../chapter_module/header/chapter_module.h"

class TextureChapterModule : public ChapterModule
{
public:
    TextureChapterModule() = default;
    // // 主代理方法
    void deletegateMain(GLFWwindow* window) override;
    // // 加载纹理；
    void generateTexture();
};
#endif // TEXTURE_1_H
