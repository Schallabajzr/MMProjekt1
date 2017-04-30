Navodila:
bash (Windows bash for linux v powershell-u)  
$ gcc -std=c99 -o p1 projekt1.c  
$./p1 velikost parameter1 parameter2
  - velikost (int) = matrika nxn
  - parameter1 (string) =
      - color: matrika se bo pobarvana izrisala v konzoli in v vsakem koraku verige, spodaj je količina posamezne barve
               in procent barve glede na velikost
      - number: matrika celih števil se bo izrisala v konzoli in v vsakem koraku verige, spodaj je količina posamezne barve
                in procent barve glede na velikost
      - para: izriše začetno stanje in procente, ter izpiše procente barv po 1000 iteracijah (glede na to kolikokrat je katera zmagala)
  - parameter2 (string) (opcijski) =
      - shroom: izvede program za predefinirano sliko gobe
      - windows: izvede program za predefinirano sliko windows logo-ta
