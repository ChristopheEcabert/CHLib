#version 330
// Input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
// uniform input -> matrix
uniform mat4 camera;

// output
out vec3 normal0;

void main() {
  // Apply transformation onto points
  gl_Position = camera * vec4(position, 1);
  // Transfer normal
  normal0 = normal;
}