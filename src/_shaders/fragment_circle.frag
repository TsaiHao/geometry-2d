#version 330 core
out vec4 fragColor;
in vec3 pos;

uniform vec3 center;
uniform float radius;

void main()
{
    if (distance(pos, center) < radius) {
        fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    } else {
        discard;
    }
}