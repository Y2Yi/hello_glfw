//
// Created by 岳郅宇 on 2024/7/13.
//

#include "gl_helper.h"

#include <iostream>
#include <glad/glad.h>

void getVertexAttributeCount()
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}
