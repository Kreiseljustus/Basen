$input a_position
$input a_normal
$output v_color0

#include "common.sh"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

    vec3 normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);

    vec3 lightDir = normalize(vec3(0.3,1.0,0.2));

    float ambient = 0.2;

    float diffuse = max(dot(normal,lightDir), 0.0);

    float brightness = clamp(ambient + diffuse * 0.8, 0.0, 1.0);

    v_color0 = vec4(brightness, brightness, brightness , 1);
}
