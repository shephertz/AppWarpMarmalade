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
