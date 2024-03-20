#version 300 es

layout(location = 0) in vec4 vPosition; 
layout(location = 1) in vec2 tex;

out vec2 TexCoord;

void main()
{ 
    gl_Position =vec4(vPosition.x,vPosition.y,vPosition.z, 1.0);
    TexCoord = tex;
} 