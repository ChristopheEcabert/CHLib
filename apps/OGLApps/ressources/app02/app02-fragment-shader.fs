#version 330
// input
in vec2 tex_coord0;
// output
out vec4 fragColor;

struct TexMaterial {
  // diffuse texture map
  sampler2D diffuse;
};

// uniform
uniform TexMaterial texture_material[1];

void main() {
  fragColor = texture(texture_material[0].diffuse, tex_coord0);
}
