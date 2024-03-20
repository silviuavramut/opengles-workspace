#version 300 es

precision mediump float;

out vec4 FragColor;

uniform vec4 uniformColor;
uniform sampler2D theTexture;
in vec2 TexCoord;

void main()
{                                         
   FragColor = texture(theTexture, TexCoord);
} 
