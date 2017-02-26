#version 330
// input
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
  vec3 normal0;
} gs_in[];

uniform float time;

// Output normal
out vec3 normal1;

// Compute triangle's normal
vec3 GetNormal() {
  vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
  vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
  return normalize(cross(a,b));
}
// Explode triangle
vec4 Explode(vec4 position, vec3 normal) {
  float magnitude = 0.03f;
  vec3 dir = normal * ((sin(0.00314f * time) + 1.f) / 2.f) * magnitude;
  return position + vec4(dir, 0.f);
}

void main() {
  // Compute normal
  vec3 n = GetNormal();
  // Explode triangle, vertex 0
  gl_Position = Explode(gl_in[0].gl_Position, n);
  normal1 = gs_in[0].normal0;
  EmitVertex();
  // Explode triangle, vertex 1
  gl_Position = Explode(gl_in[1].gl_Position, n);
  normal1 = gs_in[1].normal0;;
  EmitVertex();
  // Explode triangle, vertex 2
  gl_Position = Explode(gl_in[2].gl_Position, n);
  normal1 = gs_in[2].normal0;;
  EmitVertex();
  // Done
  EndPrimitive();
}
