AppWarpCpp
==========

AppWarp SDK for Marmalade

To use AppWarp SDK, copy the appwarp folder with your project folder. In your mkb file, define appwarp module path using

`define option module_path="../appwarp"` 

and add appwarp and iwhttp to your subproject.

```
subproject
{
	appwarp
	iwhttp
}

```

Example MKB file

```
option module_path="../appwarp"
subproject
{
  appwarp
	iwhttp
}

files
{
	(source)
	main.cpp
}
```

Running the MKB file

Simply double click on the mkb file and it should generate either a xcode or visual studio project. For your application
to build and link properly you need to ensure that your library search path and linker flags are correct. In most cases, if 
you have setup your mkb file correctly this - there should not be any further steps. However if you are getting linking
errors, make sure of the following

1. Your **library include path** contains the path to the appwarp lib for your target eg: AppWarpMarmalade/appwarp/lib/macos_x86 should be included if you are build target is x86 on Mac.
2. Your **linker flag** contains -lappwarp_d or -lappwarp (depending on whether you are building a debug or release flavour)


AppWarp SDK internally uses cJSON for serializing and deserializing JSON data.

```
 Copyright (c) 2009 Dave Gamble

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

/*cJSON */
/* JSON parser in C. */
```
