Napisao sam ovaj test za Javu jer mi nije radio niti jedan od testova drugih kolega, a bio sam lijen sam tra�iti gre�ke. Posebnost ovog testa je da je isklju�ivo za Javu �to omogu�uje da se program poziva unutar njega.
Test se mo�e pokretati iz Eclipsea, samo treba iskopirati klasu u njega. Ja sam ga i pokretao iz Eclipsea, a ne komandne linije.
Ne trebate mijenjati svoju klasu jer ovaj test radi promjenu standardnog ulaza i izlaza na datoteke.

Ako netko �eli samo engine usporedbe, a ve� je napravio svoje outpute, mo�e izbrisati kod izme�u 40. i 65. reda i reader.close() na kraju (SAMO reader.close(), ne close za ostale).

Da bi radilo treba napraviti sljede�e korake (pi�u i unutar klase):
1. Promijeniti konstante u redovima 21-24 tako da vode do pravih testova
	Put do npr. 12. testa u 2. labosu je kod mene C:\Users\Murta\Desktop\lab2_primjeri\test12\t.ul
	Mislim da je o�igledno �to koja konstanta zna�i.
	Paziti da se unutar klase koriste \\ kod Pathova jer je za Javu \ escape char sljede�eg
2. U 55. redu odrediti koju klasu �elite testirati

I to je to. Nakon toga bi sve trebalo raditi za labos koji je pode�en. Mo�e se podestiti za SVAKI labos.
Provjerite outpute na kraju da je sve OK.