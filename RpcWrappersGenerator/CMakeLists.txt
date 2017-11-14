PROJECT( RpcWrappersGenerator )
SET (ProjectDir ${RpcWrappersGenerator_SOURCE_DIR})
MESSAGE(STATUS "ipcgen ProjectDir: " ${ProjectDir})

FILE( GLOB RpcWrappersGenerator_SRC *.c* )
FILE( GLOB RpcWrappersGenerator_INC *.h* )
INCLUDE_DIRECTORIES(${SolutionDir}/RpcApiStorage)

ADD_EXECUTABLE( RpcWrappersGenerator ${RpcWrappersGenerator_SRC} ${RpcWrappersGenerator_INC} )
TARGET_LINK_LIBRARIES(RpcWrappersGenerator RpcApiStorage)
INSTALL(TARGETS RpcWrappersGenerator RUNTIME DESTINATION ${DestinationDir})
                                   