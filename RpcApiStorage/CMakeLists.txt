PROJECT( RpcApiStorage )
SET (ProjectDir ${RpcApiStorage_SOURCE_DIR})
MESSAGE(STATUS "RpcApiStorage ProjectDir: " ${ProjectDir})

FILE( GLOB RpcApiStorage_SRC ${ProjectDir}/*.cpp )
FILE( GLOB RpcApiStorage_INC ${ProjectDir}/*.h* )

ADD_DEFINITIONS(-DRPCAPISTORAGE_EXPORTS)
ADD_DEFINITIONS(-DSHARED_MODE)

IF (UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -fpermissive -Wno-deprecated")
ENDIF ()

ADD_LIBRARY( RpcApiStorage SHARED ${RpcApiStorage_INC} ${RpcApiStorage_SRC} )

#Static start
#set_target_properties(RpcApiStorage PROPERTIES LINK_SEARCH_START_STATIC 1)
#set_target_properties(RpcApiStorage PROPERTIES LINK_SEARCH_END_STATIC 1)
#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#Static Libs

#Set Linker flags
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

IF(UNIX)
  TARGET_LINK_LIBRARIES(RpcApiStorage ${Boost_LIBRARIES} dl ${XercesC_LIBRARY})
ELSE()
  TARGET_LINK_LIBRARIES(RpcApiStorage ${Boost_LIBRARIES} xerces-c)
ENDIF()

IF(NOT UNIX)
  INSTALL(TARGETS RpcApiStorage RUNTIME DESTINATION ${DestinationDir})
ELSE()
  INSTALL(TARGETS RpcApiStorage DESTINATION ${DestinationDir})
ENDIF()

