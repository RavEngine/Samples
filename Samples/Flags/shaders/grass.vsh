$input a_position, a_normal, i_data0, i_data1, i_data2, i_data3
$output v_normal, v_worldpos, mixFactor

#include "ravengine_shader.glsl"

void main()
{
    const float height = 3.43;
    vec4 wpos = instMul(mtxFromRows(i_data0, i_data1, i_data2, i_data3),vec4(0,0,0,1));
    a_position.x += sin(u_time[0] * -5 + wpos.x + wpos.z) * (a_position.y / height);
    vs_genmats();
    vs_store();
    mixFactor = height - a_position.y;
}
