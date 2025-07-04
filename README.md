# InputSwitch

**InputSwitch** is an Arduino library for handling digital input switches with debounce functionality using a `Timer`.

It supports both normally open (NO) and normally closed (NC) switches and offers flexible event-driven callbacks for input state changes, including:

- `onChange()` – called on any change (rising or falling)
- `onRising()` – called when the input goes HIGH
- `onFalling()` – called when the input goes LOW

## InputButton (Extension)

The library now also includes **InputButton**, a subclass of `InputSwitch`, which adds support for:

- `onClick()` – single short press
- `onDoubleClick()` – two quick presses
- `onLongPress()` – long hold press
- `onPress()` and `onRelease()` – sugar functions for `onRising()` and `onFalling()` respectively

It is especially useful for handling buttons in interactive applications.

## Dependencies
Requires the [MsTime](https://github.com/oskozach/MsTime) library.
