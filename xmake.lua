add_rules("mode.debug", "mode.release")

-- Get Raylib from the xrepo package manager
add_requires("raylib")

target("morse-recognition-trainer")
    set_kind("binary")
    add_files("src/*.c")

    if (is_plat("windows", "linux", "macosx")) then
        add_packages("raylib")
    end
    
    -- add_ldflags("-static", {force = true})

    -- Copy the assets
    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/assets")
    add_configfiles("assets/*.*", {onlycopy = true})
