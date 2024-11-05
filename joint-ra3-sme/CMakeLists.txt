set (TARGET joint-ra3-sme)

project (${TARGET})

set (LIBRARY_OUTPUT_PATH "../../modules/ra3-head")

set (CMAKE_SHARED_MODULE_PREFIX "")

find_package(Qt6 COMPONENTS Xml REQUIRED)

set(RRS_VERSION 1.3.0)

find_package(CfgReader ${RRS_VERSION} REQUIRED)
find_package(physics ${RRS_VERSION} REQUIRED)
find_package(Journal ${RRS_VERSION} REQUIRED)
find_package(filesystem ${RRS_VERSION} REQUIRED)
find_package(device ${RRS_VERSION} REQUIRED)
find_package(vehicle ${RRS_VERSION} REQUIRED)

file (GLOB INCLUDES "./include/*.h")
#file (GLOB EQP_INCLUDES "../ra3-equipment/include/*.h")
file (GLOB SOURCES "./src/*.cpp")
#file (GLOB EQP_SOURCES "../ra3-equipment/src/*.cpp")

#add_library (${TARGET} MODULE ${SOURCES} ${INCLUDES} ${EQP_SOURCES} ${EQP_INCLUDES})
add_library (${TARGET} MODULE ${SOURCES} ${INCLUDES})

target_include_directories (${TARGET} PRIVATE ./include/)
target_include_directories (${TARGET} PRIVATE ../ra3-equipment/include)

target_link_libraries (${TARGET} Qt6::Xml)
target_link_libraries (${TARGET} CfgReader)
target_link_libraries (${TARGET} physics)
target_link_libraries (${TARGET} Journal)
target_link_libraries (${TARGET} filesystem)
target_link_libraries (${TARGET} device)
target_link_libraries (${TARGET} vehicle)
