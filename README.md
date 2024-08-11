# MomRevisited (Memories Of Mars)

This is a collection of scripts and binaries which can be used to re-enable the game server and client for Memories Of Mars.

THIS IS NOT COMPLETE.  SOME FUNCTIONALITY IS WORKING BUT WORK IS STILL IN PROGRESS.

History:
  On June 25, 2024, 505 Games took servers for the game offline.  This existed as possibly 2 servers on AWS that were used for server and client registration.  They facilitated a server list and client to server matchmaking.

  Since this time, servers cannot register and will fail to start.  Clients also cannot browse for servers or be approved for connecting to any server.

  This code consists of:
  - Injection to the server to modify the login process.  This is custom code by gwog which uses a 3rd party injector application.
  - Injection to the client to allow for direct server connection via third party client injector
  - Scripts to facilitate server injection and client startup
  - Required server config changes to disable EAC and the proprietary Limbic subsystem.

## NOTES

  - You must own a licensed copy of the game to use this code.  Any other use may constitute a violation.
  - This will only work for Windows clients and servers.
  - Since EAC will be disabled, keep this in mind for potential hackers with 'improved' clients and scripts.

## Server instructions
  - This currently will only work for the Windows game server.
  - Edit your game server configs as follows

DedicatedServerConfig.cfg:
```
   "EnableEAC": false,
```
\Game\Saved\Config\WindowsServer\Engine.ini:
```
[OnlineSubsystem]
DefaultPlatformService=null
```
  - Download an injector, e.g. https://github.com/nefarius/Injector and place the 64 bit copy of Injector.exe into your game server folder, e.g. C:\Program Files (x86)\Steam\SteamApps\common\Memories Of Mars - Dedicated Server.
  - Place the compiled MomRevisited.dll from this repo into your Windows game server folder.
  - Place the batch file, inject.bat from this repo, into the same game server folder.
  - Start the server, either from the command line RunServer.bat or via Steam (whichever works)
  - Run the inject.bat to patch the server.  This should return:

Injector x64 [Version 20240218]
Copyright (c) 2009 Cypher, 2012-2024 Nefarius. All rights reserved.

Successfully injected module!

  - To see that output, you would need to run the batch file in cmd.exe.
  - For subsequent runs, you will need to run the game server followed by the injection script.

## Client instructions

 - Download and unpack UUU from https://framedsc.com/GeneralGuides/universal_ue4_consoleunlocker.htm
 - Copy the game.bat file from this repo to your game client folder, e.g. C:\Program Files (x86)\Steam\SteamApps\common\Memories Of Mars.
 - Edit the file to ensure that the path to the game EXE is correct:

Example:
"C:\Program Files (x86)\Steam\SteamApps\common\Memories Of Mars\MarsClient\Game\Binaries\Win64\MemoriesOfMars.exe" -noeac

Maintain the quotes since the path contains spaces.

  - Start the game client using game.bat
  - Run UuuClient.exe from the unpacked UUU folder
  - Press select and search for MemoriesOfMars.exe in the process list
  - Select MemoriesOfMars.exe and press Select - this patches the live game to allow it to connect via console to your server.
  - In game, open console using ` - This may present as a single line at the bottom of your screen or at the top (have seen both).
  - Type the following:

open {IPADDRESSOFSERVER}?accid=ABC123?authticket=ABC123?gender={MALE/FEMALE}?bSpawnBot=false

  - Replace IPADDRESSOFSERVER with your server ip, e.g. 127.0.0.1 or whatever machine is hosting the server.
  - Replace {MALE/FEMALE} with either male or female

open 127.0.0.1?accid=ABC123?authticket=ABC123?gender=male?bSpawnBot=false

  - Each time you run the game, you will need to run UUU and select the running game client.
  - Server connection will always be via the open string in the console (`)
  - The client does remember console entries, and you can use the up and down arrows to cycle through past commands
  - There is (currently) no server browser

## Compilation

This is optional, but you may compile the MoMRevisited.dll yourself if you wish.

It requires minhook, which can be retrieved from NuGet.

Once you have the minhook extension, you will need to rename or copy the most recent version from your packages folder:

  - Look in \MoMRevisited\packages\minhook.1.3.3\lib\native\lib
  - Find, e.g., libMinHook-x64-v140-md.lib and rename or copy to libMinHook.lib
  - You must select the 64 bit version, and several 64 and 32 bit versions will appear in this folder.  Choose the most recent.
  - We are using Visual Studio, not VS Code.  YMMV.

## Status
  - Server running and accepting direct connections (8 Aug 2024)
  - Client able to connect via console using UUU (8 Aug 2024)
  - TODO: On reconnect, client appears as a new player, losing progress.

Note that any buildings and devices you deploy will persist, and you will still have access.  However, your inventory will be wiped on reconnect, and you may lose some or all blueprints.

