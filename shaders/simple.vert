#version 330 core
attribute vec3 vPosition;
vec4 tPosition;
float minimum = 0;
float maximum = 5;
float r, g, b;
uniform vec4 color;
out vec4 vertColor;

uniform mat4 MVP;

float map(float x, float in_min, float in_max, float out_min, float out_max);

void main() {
    tPosition.xy = vPosition.xy;
    tPosition.w = 1;

    if(vPosition.z <= 0.05f){
        tPosition.z = -100000.0f;
    } else {
       tPosition.z = map(vPosition.z, 0, 10000, 0, 10);
    }

    //calculate color
    float ratio = 2 * (tPosition.z - minimum) / (maximum - minimum);
    float b = max(0, 1.0f * (1 - ratio));
    float r = max(0, 1.0f * (ratio - 1));
    float g = 1.0f - b - r;

    vertColor = vec4(r,g,b,1);

    gl_Position = MVP * tPosition;
    //gl_PointSize = 15.0;
}

float map (float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}