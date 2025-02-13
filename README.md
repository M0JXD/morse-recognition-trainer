# Morse Recognition Trainer

![screenshot](assets/screenshot.png)

A simple cross platform app to learn morse using a sort of Koch inspired method. 
Built with C and Raylib.

## User Guide

When not in Lesson Mode, clicking/tapping/typing the letters will simply play the morse for that letter, letting you know in the at the bottom which letter is playing. This is useful if you want to hear the letters outside of lessons. The letters will still be highlighted with your progress from Lesson Mode.

Press `Lesson` to start lesson mode, it will change to a filled button. A lesson begins by teaching you the morse for a letter, by highlighting the center for the letter that's introduced in RED and playing it's morse. Letters learnt in previous lessons have green centers. You can press `Lesson` again at any time to return to Normal Mode.

After this, the morse for a letter will play. Enter the right letter, and the meter for the letter will progress a segment.

Once you reach two segements for a letter, you will move to the next lesson and the next letter will be introduced. 
The order is the same as LCWO. The currently active letters are played at random.

If you get the letter wrong, the progress meter for the letter you should have pressed will regress. Subsequent incorrect inputs will not affect the status, but the program will wait until you enter the correct answer. Because you did not get it right on the first try, the letter will not be updated when you get in right.

If you drop to zero segements for an active letter, the program reverts back to the lesson of which that letter was introduced. Letters do not get repeated after the initial introduction, if you want to hear it again switch out of Lesson Mode and click the newly added circle.

I see no way to approach this better, as the Koch method relies on you knowing all the letters of the previous lesson before moving on. Hopefully this should be a rare occurence for most learners!

The `Theme` button changes the light/dark theme. Your preference will be saved.
The Koch method recommends listening to letters at 20WPM. Hence by default morse is at 700Hz tone 20WPM.
Click/tap the `WPM` and `Tone` buttons to cycle through other options, your preference will be saved.

## Download
I currently make binaries for Linux and Windows (and hopefully soon, Android). I'm also hoping to deploy to the web via github pages. You can download them on the [releases](https://github.com/M0JXD/morse-recognition-trainer/releases) page.

Due to not owning Apple devices and an unwillingness to break their EULA's, macOS binaries are not provided, although it should build and run.
iOS is waiting on Raylib to gain iOS support, but likewise I can't provide binaries anyways...

## Installation

On Linux and Windows, this is a portable app that uses the directory it's launched in for saving/loading data and assets.
To make things feel more "installed", you can:

### Windows
Choose where you want to store the app (e.g. Documents\Apps\morse-recognition-trainer), then right click the app and pin to start.

### Linux
Choose where you want to store the app (e.g. ~/Applications/morse-recognition-trainer), and create a desktop entry in .local/share/applications.
Your desktop environment may have a GUI for making desktop entries more easily, e.g. in Cinnamon, right click the menu and select "Edit Menu".

## Compiling
If your platform is not provided for, or you simply want to build from source, you can likely do so by installing xmake and running:

```
xmake f -m release
xmake
```

Then look in `build/(PLATFORM)/(ARCH)` and for the `release` folder, which contains the executable. 
You can move and rename this folder to `morse-recognition-trainer` or whatever you wish, although you must retain it's internal structure with the assets folder in the same directory as the binary.

Which will create a folder called morse-recognition-trainer containing the executable and the assets it requires.
For Android, the build will be more complicated. See the Android branch Raymob README.
Likewise, deploying to the web is somewhat involved.

## Credits
Made for my Dad, love you!! xx <br>
Inspired by [Morse Trainer for Windows 10](https://apps.microsoft.com/detail/9wzdncrdlzhg?hl=en-us&gl=US), which sadly became a paid app and only ran on Windows anyways. <br>
Thanks to Raysan5 and all the contributors to Raylib! <br>