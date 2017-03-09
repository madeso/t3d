FILE(GLOB app_src_glob *.cc;*.h;*.inl)
set(app_src ${app_src_glob} "${PROJECT_BINARY_DIR}/t3d-config.h")

source_group("" FILES ${app_src})
source_group(cmake FILES "${PROJECT_SOURCE_DIR}/t3d-config-in.h")

set(all_src ${app_src} "${PROJECT_SOURCE_DIR}/t3d-config-in.h" ${src_glew} ${src_soil} ${src_jsoncpp} ${src_lua})

message(STATUS "Linking with OpenGL ${OPENGL_LIBRARIES}")

add_executable(t3d WIN32 ${all_src})

target_link_libraries(t3d ${OPENGL_LIBRARIES} ${wxWidgets_LIBRARIES} )
