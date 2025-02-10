add_rules("mode.debug", "mode.release")
add_requires('raylib')

target("morse-recognition-trainer")
    set_kind("binary")
    add_files("src/*.c")
    add_packages('raylib')

    -- Copy the assets for building/running with xmake in development
    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/assets")
    add_configfiles("assets/*.*", {onlycopy = true})

    -- TODO: Install rules
    -- on_install()