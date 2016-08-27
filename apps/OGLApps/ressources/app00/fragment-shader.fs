#version 330
// input
in vec3 normal0;
// output
out vec4 fragColor;
void main() {
  vec3 light_dir = vec3(0.0, 0.0, 1.0);
  float cos_theta = clamp( dot(normal0, light_dir), 0, 1);
  //fragColor = vec4(vec3(1.0, 1.0, 1.0) * cos_theta, 1.0);
  fragColor = vec4(normal0, 1.0);
}