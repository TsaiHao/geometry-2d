#version 330 core
in vec3 pos;
out vec4 fragColor;
uniform vec3 center;

void main()
{
    if (distance(pos, center) > 0.3f) {
        fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
        fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
}