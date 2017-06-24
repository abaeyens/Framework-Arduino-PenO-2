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
