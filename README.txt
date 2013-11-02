

This a fork of https://github.com/MrBlueXav/USB_host_HID_demo intended for developing USB gamepad support for the bitbox console.

The HID USB host demo is for the STM32F4 Discovery board.

When a mouse/gamepad is connected:
The Blue Led should turn on.. Otherwise, desconnect the mouse or push the RESET button.
Clicking on the Left button of the mouse the green LED toggles
Clicking on the right button of the mouse the Red LED toggles
Clicking on the middle button of the mouse the orange LED toggles
moving the mose toggle the blue LED
Disconnecting the mouse from the Discovery board turns off all LEDs

When a Keyboard is connected:
The Blue Led should turn on.. Otherwise, desconnect the mouse or push the RESET button.
Hitting any key on the keyboard toggles the orange LED.
Disconnecting the mouse from the Discovery board turns off all LEDs

Cycle counting for the USB stack calls is done in main() with the vars cc_tot,cc_cnt and cc_max.
Cycle counting for the USB interrupt handler is done with the vars icc_tot,icc_cnt and icc_max.

