$input a_position
$output v_color0

#include "common.sh"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

    float bright = 1 + 0.5 * a_position.y;

    v_color0 = vec4(bright, bright,bright , 1);
}
