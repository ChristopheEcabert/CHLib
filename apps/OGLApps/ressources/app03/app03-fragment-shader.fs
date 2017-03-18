#version 330 core
// input
in vec3 normal0;
in vec2 tex_coord0;
// output
out vec4 fragColor;

struct TexMaterial {
  // diffuse texture map
  sampler2D diffuse;
  // specular texture map
  sampler2D specular;
  // normal texture map
  sampler2D normal;
};

// uniform
uniform TexMaterial texture_material[1];

void main() {
  fragColor = vec4(texture(texture_material[0].diffuse, tex_coord0).xyz, 1.f);
}
