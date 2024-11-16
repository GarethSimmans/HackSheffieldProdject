const std = @import("std");
const microzig = @import("microzig");

const rp2040 = microzig.hal;
const adc = rp2040.adc;
const time = rp2040.time;
const gpio = rp2040.gpio;

const pin_config = rp2040.pins.GlobalConfiguration{
    .GPIO25 = .{
        .name = "led",
        .direction = .out,
    },
};

pub fn main() void {
    const pins = pin_config.apply();
    adc.apply(.{
        .round_robin = .{
            .ain0 = true,
            .ain1 = true,
        },
    });

    while (true) {
        const sample = adc.convert_one_shot_blocking(adc.input(0)) catch 0;
        const sample2 = adc.convert_one_shot_blocking(adc.input(1)) catch 0;

        if (sample > 80) {
            pins.led.put(0);
        }
        if (sample2 > 80) {
            pins.led.put(1);
        }
    }
}
