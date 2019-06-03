aux_source_directory(ui module_ui)
aux_source_directory(ui/scene module_ui)
aux_source_directory(util module_util)
aux_source_directory(core module_core)

set(libs
        ${module_core}
        ${module_ui}
        ${module_util})

#foreach(lib ${libs})
#    message(${lib})
#endforeach()

add_library(library-queue STATIC
        ${libs})

target_include_directories(library-queue PUBLIC
        /)