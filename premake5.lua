workspace "c2"
    cdialect "C17"
    configurations { "Debug", "Release" }

project "c2"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**" }
