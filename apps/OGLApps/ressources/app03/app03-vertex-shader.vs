#version 330 core
// Input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
// uniform input -> matrix
uniform mat4 camera;

// output
out vec3 normal0;
out vec2 tex_coord0;

void main() {
  // Apply transformation onto points
  gl_Position = camera * vec4(position, 1.f);
  // Transfer normal
  normal0 = normal;
  // Transfer tex coord
  tex_coord0 = tex_coord;
}
