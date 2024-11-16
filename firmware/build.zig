const std = @import("std");
const microzig = @import("microzig/build");
const rp2040 = @import("microzig/port/raspberrypi/rp2xxx");

pub fn build(b: *std.Build) void {
    const mz = microzig.init(b, .{});
    const target = rp2040.boards.raspberrypi.pico;
    const optimize = b.standardOptimizeOption(.{});

    const firmware = mz.add_firmware(b, .{
        .name = "firmware",
        .root_source_file = b.path("src/main.zig"),
        .optimize = optimize,
        .target = target,
    });
    mz.install_firmware(b, firmware, .{});
    mz.install_firmware(b, firmware, .{ .format = .elf });
}
