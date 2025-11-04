#include "gl_helper.h"
#include "stdio.h"

void hGL_bindMat4(GLuint program, char* parram, mat4 mat) {
    GLint location = glGetUniformLocation(program, parram);
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat.m[0][0]);
}

void hGL_CreateCube(vertex* buffer, int s_index, vec3 p, vec4 co, vec3 s, vec4 t)
{
    // Pre-calc corners
    float x0 = p.f[0] - s.f[0];
    float x1 = p.f[0] + s.f[0];
    float y0 = p.f[1] - s.f[1];
    float y1 = p.f[1] + s.f[1];
    float z0 = p.f[2] - s.f[2];
    float z1 = p.f[2] + s.f[2];

    // UVs
    float u0 = t.f[0], v0 = t.f[1];
    float u1 = t.f[2], v1 = t.f[3];

    int i = s_index;

    vec4 c;
    // LEFT (-X)
    c = vector4_scalar(co, 0.8f);
    buffer[i++] = (vertex){ x0,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x0,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x0,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x0,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x0,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x0,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };

    // RIGHT (+X)
    c = vector4_scalar(co, 0.9f);
    buffer[i++] = (vertex){ x1,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x1,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x1,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x1,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x1,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x1,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };

    // BACK (-Z)
    c = vector4_scalar(co, 0.8f);
    buffer[i++] = (vertex){ x1,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x0,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x0,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x1,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x0,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x1,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };

    // FRONT (+Z)
    c = vector4_scalar(co, 0.9f);
    buffer[i++] = (vertex){ x0,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x1,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x1,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x0,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x1,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x0,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };

    // BOTTOM (-Y)
    c = vector4_scalar(co, 0.4f);
    buffer[i++] = (vertex){ x0,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x1,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x1,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x0,y0,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
    buffer[i++] = (vertex){ x1,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x0,y0,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };

    // TOP (+Y)
    c = vector4_scalar(co, 1.f);
    buffer[i++] = (vertex){ x0,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x1,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v0 };
    buffer[i++] = (vertex){ x1,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x0,y1,z1,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v0 };
    buffer[i++] = (vertex){ x1,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u1,v1 };
    buffer[i++] = (vertex){ x0,y1,z0,  c.f[0],c.f[1],c.f[2],c.f[3],  u0,v1 };
}

/*
mat4 hGL_CamToMat(struct camera* camera){
    mat4 matrix = matrix_identity();
    matrix = matrix_translate(matrix, vector_negate(camera->pos));
    matrix = matrix_rotate(matrix, (vec4) { 0, 1, 0, camera->rot.f[1] }); // yaw
    matrix = matrix_rotate(matrix, (vec4) { 1, 0, 0, camera->rot.f[0] }); // pitch

    return matrix;
}
*/
