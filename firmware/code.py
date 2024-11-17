import board
import keypad
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

key_pins = (
    board.GP1,
    board.GP2,
)

key_code = (
    Keycode.J,
    Keycode.K,
)

kbd = Keyboard(usb_hid.devices)

keys = keypad.Keys(key_pins, value_when_pressed=False, pull = True)

while True:
    event = keys.events.get()
    if event:
        if event.pressed:
            kbd.send(key_code[event.key_number])

