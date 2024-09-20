workspace "c2"
    cdialect "C17"
    configurations { "Debug", "Release", "Test" }

    filter "configurations:Test"
        defines { "DEBUG", "TEST" }
        flags { "Symbols" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

project "c2"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**" }
    removefiles {
        "src/test.c",
        "src/**test.h",
    }

project "c2-test"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}/test"

    files { "src/**" }
    removefiles { "src/main.c" }
