# Lifto simuliatorius

Visas kodas susidaro is lifto objekto, panaudojant SFML biblioteka (https://www.sfml-dev.org)


####Visas kodas veikia pagal atributus ar konstantas.
Noredami pakeisti lifto parametrus ar aukstu skaiciu, uztenka pakeisti viena parametra
Galimybe redaguoti siuos parametrus, nenukenciant veikimui:
```
- lifto aukstis
- lifto plotis
- krastu plotis (pastato)
- lifto pozicijos pradzia (virsus, kaire puse)
- tarpai tarp liftu
- greitis
- stovejimo laikas (ilaipinant ar islaipinant keleivius)
- aukstu skaicius
```

####Prideta "debug" informacija, kuri padeda lengviau issiaskinti kur ivyko klaida.
Siuo metu debug metodu isgaunama informacija:
```
- Artimiausias liftas
- Kuriame aukste randasi liftas
- Lifto status (juda aukstyn/zemyn, laukia nurodymu)
- Is kurio auksto buvo gautas iskvietimas
- I kuri auksta buvo nurodytas iskvietimas
- I kuria krypti keliaus zmogus isedes i lifta 
- Kuri butent salyga suveike pasirenkant atitinkama lifta
```

####Veikimo salyga

Ar liftas yra arciausiai (bei kyla ta pacia kryptim is kur buvo gautas iskvietimas arba liftas stovi vietoje)
Taip pat tikrina ar nera jau pravaziaves tos vietos.

Taip pat pridetas rusiavimas, jeigu zmogus nuspaude keliauti zemyn is 5 auksto, bet liftas turi sustoti 6 aukste.
Tai liftas pradziai nukeliaus i 6 auksta ir tik veliau keliaudamas zemyn, sustos pasiimti is 5 auksto.

####Lifto spalvu reiksmes
| Spalva | Reiksme|
| ------ | ------ |
| Raudona | Liftas stovi|
| Zalia | Liftas kyla i virsu|
| Melyna | Liftas kyla i apacia|
| Geltona | Liftas ilaipina ar islaipina keleivius|