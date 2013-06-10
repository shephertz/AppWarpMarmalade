AppWarpMarmalade
================

AppWarp SDK for Marmalade

To use AppWarp SDK, copy the appwarp folder in the same directory as your project folder. In your mkb file, define appwarp module path using

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
