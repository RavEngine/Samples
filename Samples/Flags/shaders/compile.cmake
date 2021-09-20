# flag shader
declare_shader("flag" "${CMAKE_CURRENT_LIST_DIR}/flag.vsh" "${CMAKE_CURRENT_LIST_DIR}/flag.fsh" "${CMAKE_CURRENT_LIST_DIR}/flag_varying.def.hlsl")

# flag shader that does not use a texture
declare_shader("flag_special" "${CMAKE_CURRENT_LIST_DIR}/flag.vsh" "${CMAKE_CURRENT_LIST_DIR}/flag_special.fsh" "${CMAKE_CURRENT_LIST_DIR}/flag_varying.def.hlsl")
