#version 130

uniform sampler2D texture;
uniform vec3 r_mix;
uniform vec3 g_mix;
uniform vec3 b_mix;
uniform float is_enabled;

void main() {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;

    if (is_enabled < 0.5) {
        gl_FragColor = pixel;
    } else {
        float r = (pixel.r * r_mix.x) + (pixel.g * r_mix.y) + (pixel.b * r_mix.z);
        float g = (pixel.r * g_mix.x) + (pixel.g * g_mix.y) + (pixel.b * g_mix.z);
        float b = (pixel.r * b_mix.x) + (pixel.g * b_mix.y) + (pixel.b * b_mix.z);
        
        gl_FragColor = vec4(r, g, b, pixel.a);
    }
}