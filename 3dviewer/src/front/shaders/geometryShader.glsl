#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in vec4 vertexColor[];

uniform vec2 u_resolution;
uniform float u_lineWidth;

out float texCoord;   // Параметр вдоль линии (0-1)
out vec4 gColor;

void main() {
    vec3 p0 = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
    vec3 p1 = gl_in[1].gl_Position.xyz / gl_in[1].gl_Position.w;
    // vec3 view_dir = vec3(0) - p0;
    vec3 view_dir = vec3(0,0,-1);
    vec3 tangent = p0 - p1;
    tangent = normalize(tangent);
    vec3 offset_dir = cross(view_dir,tangent);
    offset_dir = normalize(offset_dir);

    // linewidth_norm = 2.0 * u_lineWidth / u_resolution / 2.0 цифры сокращаются
    float linewidth_norm_x = u_lineWidth / u_resolution.x ;
    float linewidth_norm_y = u_lineWidth / u_resolution.y ;
    //оффсет по длинной стороне
    vec3 offset = vec3(offset_dir.x *linewidth_norm_x, offset_dir.y * linewidth_norm_y , offset_dir.z * sqrt(linewidth_norm_x * linewidth_norm_y));
    //оффсет по короткой стороне
    vec3 offset_tan = vec3(tangent.x *linewidth_norm_x, tangent.y * linewidth_norm_y , tangent.z * sqrt(linewidth_norm_x * linewidth_norm_y));
    
    // Передаём local_pos в диапазоне [0, длина линии]
    float len = length(p1 - p0);
    
    vec4 pos0_plus = vec4(p0 + offset + offset_tan, 1);
    gl_Position = pos0_plus;
    texCoord = 0.0;
    gColor = vertexColor[0];
    EmitVertex();

    vec4 pos0_minus = vec4(p0 - offset + offset_tan, 1);
    gl_Position = pos0_minus;
    texCoord = 0.0; 
    gColor = vertexColor[0];
    EmitVertex();

    vec4 pos1_plus =  vec4(p1 + offset - offset_tan, 1);
    gl_Position = pos1_plus;
    texCoord = 1.0;
    gColor = vertexColor[1];
    EmitVertex();

    vec4 pos1_minus = vec4(p1 - offset - offset_tan, 1);
    gl_Position = pos1_minus;
    texCoord = 1.0;
    gColor = vertexColor[1];
    EmitVertex();

    EndPrimitive();
}
