#version 330
// input
in vec2 tex_coord0;
// output
out vec4 fragColor;
// uniform
uniform sampler2D obj_texture;

void main() {
  fragColor = texture(obj_texture, tex_coord0);
  //fragColor = vec4(1.f,1.f,1.f,1.f);
}
