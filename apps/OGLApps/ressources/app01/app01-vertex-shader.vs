#version 330
// Input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
// uniform input -> matrix
uniform mat4 camera;

// output
out VS_OUT {
  vec3 normal0;
} vs_out;

void main() {
  // Apply transformation onto points
  gl_Position = camera * vec4(position, 1);
  // Transfer normal
  vs_out.normal0 = normal;
}
