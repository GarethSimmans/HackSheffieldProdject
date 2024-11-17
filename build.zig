const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "taiko",
        .optimize = optimize,
        .target = target,
        .link_libc = true,
    });
    exe.root_module.addCSourceFiles(.{
        .files = &files,
        .flags = &flags,
    });
    exe.root_module.linkSystemLibrary("raylib", .{});

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    if (b.args) |args| run_cmd.addArgs(args);
    const run_step = b.step("run", "run the app");
    run_step.dependOn(&run_cmd.step);

    const recorder = b.addExecutable(.{
        .name = "recorder",
        .optimize = optimize,
        .target = target,
        .link_libc = true,
    });
    recorder.root_module.addCSourceFile(.{
        .file = b.path("src/rec.c"),
        .flags = &flags,
    });
    recorder.root_module.linkSystemLibrary("raylib", .{});

    b.installArtifact(recorder);

    const rec_run_cmd = b.addRunArtifact(recorder);
    if (b.args) |args| run_cmd.addArgs(args);
    const rec_run_step = b.step("run-rec", "run the app");
    rec_run_step.dependOn(&rec_run_cmd.step);
}

const files = [_][]const u8{
    "src/main.c",
};

const flags = [_][]const u8{
    "-Wall",
    "-Wextra",
    "-pedantic",
    "-std=c99",
};
