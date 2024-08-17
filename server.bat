set OPENSSL_ia32cap=:~0x20000000
START /B "" "C:\Program Files (x86)\Steam\steamapps\common\Memories of Mars - Dedicated Server\Game\Binaries\Win64\MemoriesOfMarsServer.exe"
sleep 15s
Injector.exe --process-name MemoriesOfMarsServer.exe --inject MomRevisited.dll
