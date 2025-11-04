#pragma once
// Vertex Shader Source with texture!!
const char* mesh_vert =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"  // Change to vec2 for texture coordinates
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"    ourColor = aColor;\n"
"    TexCoord = aTexCoord;\n"  // Add the semicolon here
"}\n";

// Fragment Shader Source
const char* mesh_frag =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"  // Texture coordinates passed from the vertex shader
"uniform sampler2D texture1;\n"  // The texture
"void main() {\n"
"    vec4 textureColor = texture(texture1, TexCoord);  // Sample the texture\n"
"    FragColor = textureColor * vec4(ourColor, 1.0);  // Combine texture color with vertex color\n"
"}\n";

const char* text_vert =
"#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"      // Position in object space
"layout(location = 1) in vec2 aTexCoord;\n" // Texture coordinate
"uniform mat4 projection;\n" // Orthographic projection
"uniform mat4 model;\n"      // Transform for scaling/moving HUD element
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"	gl_Position = projection * model * vec4(aPos, 0.0, 1.0);\n"
"	TexCoord = aTexCoord;\n"
"}\n";

const char* text_frag =
"#version 330 core\n"
"in vec2 TexCoord;\n"
"uniform sampler2D hudTexture;\n"
"uniform vec4 color;\n" // optional tint
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	vec4 texColor = texture(hudTexture, TexCoord);\n"
"	FragColor = texColor * color;\n" // use vec4(1.0) for no tint
"}\n";

