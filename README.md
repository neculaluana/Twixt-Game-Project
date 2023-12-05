# Twixt - Strategy Game for Two
### Team Members:
- Marin Alexandra
- Mihai Luciana
- Necula Luana
- Popica Stefania

### Requirements:
- VS Qt Extension

Installation Steps:
To start, you need to be in a project, go up to the toolbar and select:
Extensions > Manage Extensions and grab the Qt Visual Studio Tools extension.
Once you click to install the extension, you will need to exit VS, after which an extension installation window will appear. Here click on modify and wait for it to install
After you log back into visual studio or right after the extension installs, you should get a popup to choose the version of Qt. If you accidentally closed the popup, no problem, you can find it when you log back into Visual Studio, under Extensions > Qt VS Tools > Qt Versions.
Here press +, look for where you installed Qt > 6.x.x (your version) > msvc2019_64 > bin and select qmake.exe

Now you can create projects in Visual Studio (make a project like any other, except instead of empty project select Qt widget application).
