# STATIC 또는 SHARED 선택 가능 
option(BUILD_SHARED_LIBS "Build using shared libraries" ON) 

add_library(mathFunctions mathFunctions.cpp) 

target_include_directories(mathFunctions PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
# 설치 규칙 
install(TARGETS mathFunctions 
		EXPORT mathFunctionsTargets 
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib 
		RUNTIME DESTINATION bin) 
install(FILES include/mathFunctions.h DESTINATION include)
