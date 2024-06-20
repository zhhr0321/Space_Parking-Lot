set(source_list pms.cpp vehicle.cpp parkinglot.cpp) # add your .cpp files here

add_executable(pms ${source_list})
add_executable(pms-asan ${source_list})

target_compile_options(pms-asan PRIVATE -DNO_GUI -DDEBUG)
target_compile_options(pms-asan PRIVATE -DDEBUG -g -fsanitize=address,leak,undefined,integer,bounds,float-divide-by-zero,float-cast-overflow -fno-omit-frame-pointer -fno-sanitize-recover=all)
target_link_options(pms-asan PRIVATE -fsanitize=address)
