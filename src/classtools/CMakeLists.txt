add_library(classtools SHARED classtools.cpp)
target_link_libraries(classtools LINK_PUBLIC fileio)
target_link_libraries(classtools LINK_PUBLIC controls)
target_link_libraries(classtools LINK_PUBLIC cerr)
target_link_libraries(classtools LINK_PUBLIC tools)
target_link_libraries(classtools LINK_PUBLIC basisset)
target_link_libraries(classtools LINK_PUBLIC molecule)
target_link_libraries(classtools LINK_PUBLIC ${EXTERNAL_CQ_DEPS})


if(USE_LIBINT)
if(BUILD_LIBINT)
 add_dependencies(classtools libint)
endif()
endif()
