#version 330 core

layout (location = 0) in vec3 in_position;

out vec3 texture_coordinates;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // view - discarding camera translation
    vec4 position = projection * mat4(mat3(view)) * vec4(in_position, 1.0); 
    gl_Position = position.xyww;
    texture_coordinates = in_position;
} 