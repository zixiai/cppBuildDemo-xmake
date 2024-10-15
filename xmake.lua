-- 项目配置
set_xmakever("2.9.0")
set_policy("package.requires_lock", true)

-- 项目设定配置
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

-- 项目添加依赖
-- add_requires("xxx", {configs = {shared = true}}) -- shared demo
add_requires("boost 1.86.0", {configs = {headers = true}})
add_requires("ffmpeg 7.0")
add_requires("glog 0.7.1")
add_requires("gtest 1.15.2")
add_requires("libhv 1.3.2", {configs = {openssl = true}})
add_requires("opencv 4.10.0")
add_requireconfs("opencv.ffmepg", {version = "7.0", override = true})
add_requires("protobuf-cpp 3.19.4")
add_requires("simpleini 4.22")
add_requires("sqlitecpp 3.3.2")


-- 目标 cppBuildDemo-xmake
target("cppBuildDemo-xmake")
    -- 目标编译对象
    set_kind("binary")
    add_files("src/*.cpp")

    -- 目标模板配置文件
    add_configfiles("src/config.h.in")
    set_configdir("$(buildir)/config")

    -- 目标链接依赖库
    add_packages("boost", "ffmpeg", "glog", "gtest", "libhv", "opencv", "protobuf-cpp", "simpleini", "sqlitecpp")






--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

