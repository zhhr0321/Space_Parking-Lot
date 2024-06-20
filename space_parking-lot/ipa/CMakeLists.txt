set(source_list ipa.cpp) # add your .cpp files here

set(OpenGL_GL_PREFERENCE "GLVND")

# Find the OpenGL library (don't modify)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Find the GLUT library (don't modify)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
add_executable(ipa ${source_list})

add_executable(ipa-asan ${source_list})

# Link the OpenGL, GLUT and Maths library to your project (don't modify)
target_link_libraries(ipa ${GLUT_LIBRARIES} ${OPENGL_LIBRARY})

target_compile_options(ipa-asan PRIVATE -DNO_GUI -DDEBUG)
target_compile_options(ipa-asan PRIVATE -DDEBUG -g -fsanitize=address,leak,undefined,integer,bounds,float-divide-by-zero,float-cast-overflow -fno-omit-frame-pointer -fno-sanitize-recover=all)

target_link_options(ipa-asan PRIVATE -fsanitize=address)

