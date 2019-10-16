Što je potrebno za Windows verziju programa?

1. Microsoft Windows 98 ili noviji. 
2. CD-ROM
3. Barem 32 MB radne memorije i 20 MB slobodnog prostora na disku.
4. Ispravno konfigurirani TCP/IP protokol i Internet pretraživaè.

   

Pitanja

1.  
P: DOS prozor sa Supra aplikacijom je otvoren, no u WWW pretraživacu se ne vidi aplikacija za
   pretraživanje nego poruka o grešci.

O: Provjerite da se ne koristi proxy server za lokalne adrese. 
   
   Procedura provjere za Internet Explorer: 
   	 - Menu - View (ili Tools u novijim verzijama), Internet Options, Connection.
	 - Proxy settings, ukljuciti opciju Bypass proxy server for local addresses


2.
P: Supra.exe koristi TCP/IP i sluša nadolazece konekcije na portu 1024. Što ako se netko pokuša
   spojiti na taj TCP/IP port mog raèunala sa neke vanjske IP adrese?

O: Neæe se moæi spojiti. Supra.exe prima samo localhost (127.0.0.1) konekcije.

3. 
P: Što znaèi ispravno konfiguriran TCP/IP protokol?
O: Svako raèunalo sa Windowsima serije NT (4.0, 2000, XP) ili novijim ima ispravno 
   konfiguriran TCP/IP.

   Svako raèunalo sa instaliranim modemom ili mrežnom karticom ima
   ovako konfiguriran TCP/IP protokol. 
   
   Ukoliko vaše raèunalo nema modem niti mrežnu karticu niti Windows NT, morat æe te 
   instalirati jedan (virtualni) Dial-Up adapter. Taj virtualni adapter neæe se
   koristiti. Pošto se u Windowsima ne može posebno dodati TCP/IP loopback adapter 
   da lokalna TCP/IP mreža proradi, ovo je najjednostavnije riješenje.    

4.
P: Kako instalirati virtualni Dial-Up adapter za TCP/IP mrežu?
O: Windows 98: Control Panel -> Network -> Add... -> Adapter-> Microsoft -> Dial Up Adapter
O: Windows Millenium: Dodajte standardni modem (iako ga nemate). Dodajte Internet Connection u
   Dial-Up networkingu za izmišljenim brojevima.
