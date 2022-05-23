vec3 a_position  : POSITION;
vec3 a_normal    : NORMAL;

vec4 i_data0 : TEXCOORD7;
vec4 i_data1 : TEXCOORD6;
vec4 i_data2 : TEXCOORD5;
vec4 i_data3 : TEXCOORD4;

vec3 v_worldpos  : POSITION1 = vec3(0.0, 0.0, 0.0);
vec3 v_normal    : NORMAL    = vec3(0.0, 0.0, 0.0);
float mixFactor : TEXCOORD3;