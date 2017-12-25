#
# Function sets compilers flags
# It sets on set of flags to all variables:
# CMAKE_C_FLAGS_RELEASE, CMAKE_C_FLAGS_DEBUG,
# CMAKE_C_FLAGS_RELWITHDEBINFO and CMAKE_C_FLAGS_MINSIZEREL.
#

function(set_compiler_flags FLAGS)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} ${FLAGS}" PARENT_SCOPE)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${FLAGS}" PARENT_SCOPE)
endfunction()

#
# Function sets compilers flags.
# It sets values to correspondings variables.
#

function(set_separate_compiler_flags FLAG_RELEASE
                                    FLAG_DEBUG
                                    FLAG_RELWITHDEBINFO
                                    FLAG_MINSIZEREL)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${FLAG_RELEASE}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${FLAG_DEBUG}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${FLAG_RELWITHDEBINFO}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} ${FLAG_MINSIZEREL}" PARENT_SCOPE)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAG_RELEASE}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAG_DEBUG}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${FLAG_RELWITHDEBINFO}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${FLAG_MINSIZEREL}" PARENT_SCOPE)
endfunction()

#
# Function sets compilers flags
#
function(set_linker_flags FLAGS)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${FLAGS}" PARENT_SCOPE)
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} ${FLAGS}" PARENT_SCOPE)
endfunction()

#
# Function clear flags from compiler's flag lists.
#
function(delete_compilers_flags REGEXP_SENTENCE)
    set(FLAGS_LIST CMAKE_C_FLAGS_DEBUG
                    CMAKE_CXX_FLAGS_DEBUG
                    CMAKE_C_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_C_FLAGS_MINSIZEREL
                    CMAKE_CXX_FLAGS_MINSIZEREL
                    CMAKE_C_FLAGS_RELWITHDEBINFO
                    CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )

    foreach(FLAG_VAR ${FLAGS_LIST})
        string(REGEX REPLACE "${REGEXP_SENTENCE}" "" ${FLAG_VAR} "${${FLAG_VAR}}")
        set(${FLAG_VAR} "${${FLAG_VAR}}" PARENT_SCOPE)
    endforeach()
endfunction()
