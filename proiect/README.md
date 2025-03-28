# Proiect Programare Orientata pe Obiecte  
**Aplicatie: Sistem de ticketing**  
**Student: Iacob Alin-Ovidiu**  
**Grupa: 144**
## Descriere proiect
Aceasta aplicatie simuleaza un sistem de gestionare al biletelor si abonamentelor folosite in mijloacele de transport din Bucuresti. Ofera posibilitatea crearii a mai multor conturi, cu diferite atributii, cum ar fi un cont de utilizator, de casier, de controlor.  
**This is just the beginning of the project. I will come up with new ideas in due course!**
## Clase folosite
1. Client
   * nume
   * prenume
   * password
   * id
   * are_abonament
   * portofel(vezi mai jos _clasa Portofel_)
   * caz_special(bool)
   * caz
2. Staff
   * nume
   * prenume
   * email
   * password
   * pozitie
3. Mijloc de transport(**mai trebuie adaugate date**)
   * tip
   * pret
4. Portofel
   * fonduri
   * are_bilet(bool) **e redundant, stiu, se repeta putin cu ce este in Client, dar o sa modific**
   * are_abonament(bool)
   * tip_abonament  
### Idei, remindere, intrebari 
1. Pentru proiectul al doilea, as dori sa folosesc inheritance pe anumite clase, cum ar fi **staff** si **mijloc de transport** si **client**.
2. Cum pot face sa memorez obiectele create, in cazul meu, clientii si angajatii, si dupa terminarea programului?
3. Ar exista alta modalitate mai simpla si mai clean pentru functia **getHiddenPassword**? 
4. **Reminder for me**: Sa pun functii de afisare la clasele recent create!
5. **Alt reminder**: Sa modific in asa fel incat sa nu am de doua ori abonament(Da/Nu)
### Proiect 1
1. **Constrangere** Desi apare ca un client isi poate lua abonament, inca nu am implementat aceasta modalitate. O voi implementa pentru proiectul al 2-lea
2. Am asumat in mai multe cazuri faptul ca lumea tasteaza corect unele date
7. Daca ai intrebari, te rog sa ma contactezi la adresa [aliniacob13@yahoo.com](aliniacob13@yahoo.com)
