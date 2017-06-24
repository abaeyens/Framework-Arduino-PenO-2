# VirtualButton library

Using virtual buttons is a bit weird to say the least. However, used correctly they provide a level of abstraction which enables you to focus on the functionality of your code and not problems with variables and the like.

The library has a lot of functions to manipulate the objects and normally you only use a few of them, but they are there if you need them.

In fact there's only one thing important and that's there are two certain functions - `subtractTimeVButtons` and `subtractTimeVPedals` - which have to be called regularly. These two functions update the state of the virtual buttons and pedals.

There's currently one example which illustrates the basic usage of a virtual button object. If something isn't clear, which is very normal, don't hesitate and let me know something (post an issue). In that case, please be clear about what you want to achieve.

## Examples
- VirtualButton_example_01: Basics of using a virtual button.

## Usage
Virtual buttons are objects and thus the normal C++ stuff concerning classes and object applies. Let's create a virtual object:
```cpp
VButton SW_myButton;
```
You can give the button any name you want. In this case, we opted for the name `SW_myButton`. It might be preferable to use the buttons as global objects. In short this means that (1) you have to create the objects before the setup() code and (2) that you can use the object in the whole program.

Before that we are able to use the button we just created, we first have to register it. This has to happen only one time so it's probably best to do this in the setup().
```cpp
initVButton(&SW_myButton);
```
Note the use of the '&' in front of the name of the object. This is because we have to refer to the address of the object. We do not want to pass the whole object to the function.

The timeout time is the time the state of the button stays high after the last press. This value can be changed. It's best to do this in the setup().

```cpp
SW_myButton.timeOut = 150;
```

The current state (a boolean) is saved in the public variable `state` of the virtual button object.
```cpp
a = SW_myButton.state  // Save the state of the button to the variable 'a'.
```
For example, we can do a while-loop that runs until the button isn't pressed anymore:
```cpp
while(SW_myButton.state == true){
  // Function body...
}
```

Of course you can push a button.
```cpp
SW_myButton.push();
```
A button can also be released. A release forces the button to go low.
```cpp
SW_myButton.release();
```

A special function is the `get()`. It returns the state of button and marks the button as read. The button returns to it's normal, not-yet-read state when the timeout period after the last press has passed. If the `get()` function is used on a button that has already been read but still has the state high, it returns false.
```cpp
a = SW_myButton.get();  // Save the getted state of the button to the variable 'a'.
```

The virtual pedals work the same way. The only difference is that in addition to a low/high state they also have a position variable which increases and decreases. This position is saved in the public variable `position` of the the virtual pedal object.
