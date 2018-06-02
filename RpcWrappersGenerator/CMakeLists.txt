PROJECT( ipcgen )
SET (ProjectDir ${ipcgen_SOURCE_DIR})
MESSAGE(STATUS "ipcgen ProjectDir: " ${ProjectDir})

INCLUDE_DIRECTORIES(${SolutionDir}/RpcApiStorage)

set(ipcgen_SRC
	RpcGeneratorConfigurator.cpp
	RpcGeneratorExecutor.cpp
	RpcGeneratorExecutorInterface.cpp
	RpcWrappersGenerator.cpp
	GeneratorOptions.cpp
)

set(ipcgen_INC
	RpcGeneratorConfigurator.h
	RpcGeneratorExecutor.h
	RpcGeneratorExecutorInterface.h
	RpcWrappersGenerator.h
	GeneratorOptions.h
)

ADD_EXECUTABLE( ipcgen ${ipcgen_SRC} ${ipcgen_INC} )
set_target_properties(ipcgen PROPERTIES LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(ipcgen RpcApiStorage)
INSTALL(TARGETS ipcgen RUNTIME DESTINATION ${DestinationDir})
                                   
