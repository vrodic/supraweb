�to je potrebno za Windows verziju programa?

1. Microsoft Windows 98 ili noviji. 
2. CD-ROM
3. Barem 32 MB radne memorije i 20 MB slobodnog prostora na disku.
4. Ispravno konfigurirani TCP/IP protokol i Internet pretra�iva�.

   

Pitanja

1.  
P: DOS prozor sa Supra aplikacijom je otvoren, no u WWW pretra�ivacu se ne vidi aplikacija za
   pretra�ivanje nego poruka o gre�ci.

O: Provjerite da se ne koristi proxy server za lokalne adrese. 
   
   Procedura provjere za Internet Explorer: 
   	 - Menu - View (ili Tools u novijim verzijama), Internet Options, Connection.
	 - Proxy settings, ukljuciti opciju Bypass proxy server for local addresses


2.
P: Supra.exe koristi TCP/IP i slu�a nadolazece konekcije na portu 1024. �to ako se netko poku�a
   spojiti na taj TCP/IP port mog ra�unala sa neke vanjske IP adrese?

O: Ne�e se mo�i spojiti. Supra.exe prima samo localhost (127.0.0.1) konekcije.

3. 
P: �to zna�i ispravno konfiguriran TCP/IP protokol?
O: Svako ra�unalo sa Windowsima serije NT (4.0, 2000, XP) ili novijim ima ispravno 
   konfiguriran TCP/IP.

   Svako ra�unalo sa instaliranim modemom ili mre�nom karticom ima
   ovako konfiguriran TCP/IP protokol. 
   
   Ukoliko va�e ra�unalo nema modem niti mre�nu karticu niti Windows NT, morat �e te 
   instalirati jedan (virtualni) Dial-Up adapter. Taj virtualni adapter ne�e se
   koristiti. Po�to se u Windowsima ne mo�e posebno dodati TCP/IP loopback adapter 
   da lokalna TCP/IP mre�a proradi, ovo je najjednostavnije rije�enje.    

4.
P: Kako instalirati virtualni Dial-Up adapter za TCP/IP mre�u?
O: Windows 98: Control Panel -> Network -> Add... -> Adapter-> Microsoft -> Dial Up Adapter
O: Windows Millenium: Dodajte standardni modem (iako ga nemate). Dodajte Internet Connection u
   Dial-Up networkingu za izmi�ljenim brojevima.
