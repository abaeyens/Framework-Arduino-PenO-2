# VirtualButton library

Using virtual buttons is a bit weird to say the least. However, used correctly they provide a level of abstraction which enables you to focus on the functionality of your code and not problems with variables and the like.

The library has a lot of functions to manipulate the objects and normally you only use a few of them, but they are there if you need them.

In fact there's only one thing important and that's there are two certain functions - `subtractTimeVButtons` and `subtractTimeVPedals` - which have to be called regularly. These two functions update the state of the virtual buttons and pedals.