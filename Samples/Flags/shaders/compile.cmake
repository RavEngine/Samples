# flag shader
declare_shader("flag" "${CMAKE_CURRENT_LIST_DIR}/flag.vsh" "${CMAKE_CURRENT_LIST_DIR}/flag.fsh" "${CMAKE_CURRENT_LIST_DIR}/flag_varying.def.hlsl")

# flag shader that does not use a texture
declare_shader("flag_special" "${CMAKE_CURRENT_LIST_DIR}/flag.vsh" "${CMAKE_CURRENT_LIST_DIR}/flag_special.fsh" "${CMAKE_CURRENT_LIST_DIR}/flag_varying.def.hlsl")

# grass shader
declare_shader("grass" "${CMAKE_CURRENT_LIST_DIR}/grass.vsh" "${CMAKE_CURRENT_LIST_DIR}/grass.fsh" "${CMAKE_CURRENT_LIST_DIR}/grass.def.hlsl")
