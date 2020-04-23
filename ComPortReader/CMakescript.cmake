# src for math
if(WIN32)
    set(SRC_COM_READER_UNITS ${COM_READER_UNITS}serial_port_winapi.cpp)
else()
    set(SRC_COM_READER_UNITS ${COM_READER_UNITS}serial_port_linapi.cpp)
endif()

# library
set(LIB_NAME serial_reader_lib)
add_library(${LIB_NAME} STATIC ${SRC_COM_READER_UNITS})
