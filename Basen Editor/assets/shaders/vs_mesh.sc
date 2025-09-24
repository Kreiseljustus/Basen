$input a_position
$output v_color0

#include "common.sh"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

    float ambient = 0.2;
    float fakeLight = clamp(ambient + 0.8 * (a_position.y * 0.5 + 0.5), 0.0, 1.0);

    v_color0 = vec4(fakeLight, fakeLight,fakeLight , 1);
}
