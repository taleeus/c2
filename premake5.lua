workspace "c2"
    cdialect "C17"
    configurations { "Debug", "Release", "Test" }

    filter "configurations:Test"
        defines { "CDEBUG", "CTEST" }
        symbols "On"

    filter "configurations:Debug"
        defines { "CDEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "CRELEASE" }
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
