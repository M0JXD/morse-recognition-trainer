# Morse Recognition Trainer

A simple cross platform app to learn morse using the Koch method. 
Built with C and Raylib.

## Download
I currently make binaries for Linux, Windows and Android. You can download them on the releases page.
Due to not owning Apple devices and an unwillingness to break their EULA's, macOS binaries are not provided, although it should build and run.
iOS is waiting on Raylib to gain iOS
On Linux and Windows, this is a portable app that uses the directory it's launched in for saving/loading data and assets.

To make your install more integrated, you can:

### Windows
Right click the app and pin to start.

### Linux
Choose where you want to store the app (e.g. ~/Applications/morse-recognition-trainer), and create a desktop entry in .local/share/applications.
Your desktop environment may have a GUI for making desktop entries more easily, e.g. in Cinnamon, right click the menu and select "Edit Menu".

## Compiling
If your platform is not provided for, or you simply want to build from source, you can possibly do so by installing xmake and running:

```
xmake
xmake install
```

Which will create a folder called release containing the executable and the assets it requires.
For Android, the build is more complicated.

## Credits
Inspired by [Morse Trainer for Windows 10](https://apps.microsoft.com/detail/9wzdncrdlzhg?hl=en-us&gl=US)
Thanks to Raysan5 and all the contributors to Raylib!