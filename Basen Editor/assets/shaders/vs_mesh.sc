$input a_position
$input a_normal
$output v_color0

#include "common.sh"

uniform vec4 u_lightDir;
uniform vec4 u_lightColor;

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

    vec3 normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);

    vec3 lightDir = normalize(u_lightDir.xyz);

    float ambient = 0.2;

    float diffuse = max(dot(normal,lightDir), 0.0);

    vec3 color = u_lightColor.xyz * (ambient + diffuse * 0.8);

    v_color0 = vec4(clamp(color,0.0,1.0), 1.0);
}
