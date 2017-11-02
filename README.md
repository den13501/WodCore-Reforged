## Overview
World of Warcraft Warlords of Draenor (6.2.3.20779) emulator based on TrinityCore project, JadeCore (5.0.5), Garrosh (5.4.X)


## Downloads

[Patched Executable](http://www.mediafire.com/file/nltflkn5nx7fhci/Wow-64-Patched.exe)

[Full Client](http://wowcircle.com/files/WowCircle%206.2.3.torrent)

[dbc/vmaps/maps/mmaps](http://www.mediafire.com/file/x191aw91im1391e/ServerData.7z)


## Requirements

+ Platform: Linux, Windows or Mac
+ Git ≥ 1.7+
+ ACE ≥ 6.2.0
+ MySQL ≥ 5.5.0+ (users of MySQL 5.7 and higher need to remove NO_ZERO_DATE, NO_ZERO_IN_DATE and ONLY_FULL_GROUP_BY from the global sql_mode)
+ CMake ≥ 3.2+
+ OpenSSL ≥ 1.0.0
+ GCC ≥ 4.7.2 (Linux only)
+ MS Visual Studio ≥ 12 (2013) (Windows only, and VS2013 and VS2015 users need to modify the cmake files as discussed here: https://github.com/dufernst/FirestormWoD/issues/1)
+ Xcode 7 (Mac only)


## Install

Detailed installation guides are available in the wiki for
[Windows](http://collab.kpsn.org/display/tc/Win),
[Linux](http://collab.kpsn.org/display/tc/Linux) and
[Mac OSX](http://collab.kpsn.org/display/tc/Mac).

- If you have the message `Git was NOT FOUND on your system` please uninstall and update your git version (you can also change the path for the binary on yout PATH)
- **NEW** Windows user you need the mysql server installed, download the last version (5.7+) here : [MySQL Community Server](http://dev.mysql.com/downloads/mysql/) if you need the x86 build just change the include path on cmake
- **NEW** If you use MSVC 2013 you *MUST* have the update 3+
