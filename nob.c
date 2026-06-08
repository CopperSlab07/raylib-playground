#define NOB_IMPLEMENTATION
#include "vendor/nob.h"

void build_common_windows(Nob_Cmd *cmd, const char *exec, const char *source){
    nob_cmd_append(cmd, "gcc", "-std=c11", "-Wall", "-Wextra", "-I./vendor", "-I./vendor/raylib-6.0_win64_mingw-w64/include");
    nob_cmd_append(cmd, "-o", exec, source);
    nob_cmd_append(cmd, "-L./vendor/raylib-6.0_win64_mingw-w64/lib", "-lraylib", "-lm", "-lgdi32", "-lwinmm");
}

void build_common_linux(Nob_Cmd *cmd, const char *exec, const char *source){
    nob_cmd_append(cmd, "gcc", "-std=c11", "-Wall", "-Wextra", "-I./vendor", "-I./vendor/raylib-6.0_linux_amd64/include");
    nob_cmd_append(cmd, "-o", exec, source);
    nob_cmd_append(cmd, "-L./vendor/raylib-6.0_linux_amd64/lib", "-Wl,-rpath=./vendor/raylib-6.0_linux_amd64/lib", "-lraylib", "-lm", "-lX11", "-lXrandr", "-lGLX", "-lGL", "-lpthread", "-ldl", "-lrt");
}

int main(int argc, char **argv){
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    build_common_linux(&cmd, "grid", "grid.c");
    if(!nob_cmd_run(&cmd)) return -1;
    build_common_linux(&cmd, "cube", "cube.c");
    if(!nob_cmd_run(&cmd)) return -1;
    return 0;
}
