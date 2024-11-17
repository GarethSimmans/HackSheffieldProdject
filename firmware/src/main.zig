const std = @import("std");
const microzig = @import("microzig");

const rp2040 = microzig.hal;
const adc = rp2040.adc;
const time = rp2040.time;
const gpio = rp2040.gpio;

const led = gpio.num(25);
const output = gpio.num(16);
const output2 = gpio.num(17);

pub fn main() void {
    led.set_function(.sio);
    led.set_direction(.out);
    led.put(1);

    output.set_function(.sio);
    output.set_direction(.out);

    output2.set_function(.sio);
    output2.set_direction(.out);

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
            output.put(1);
            time.sleep_ms(9);
            output.put(0);
        }
        if (sample2 > 80) {
            output2.put(1);
            time.sleep_ms(9);
            output2.put(0);
        }
    }
}
