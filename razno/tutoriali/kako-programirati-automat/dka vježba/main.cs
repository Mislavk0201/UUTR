using System;

namespace dka_vje�ba
{
    class main
    {
        static int Main()
        {
            dka automat = new dka("q0");    //stvaramo instancu automata sa po�etnim stanjem Q0

            Console.WriteLine("Upi�i niz za provjeru: ");   //upis niza
            string ulaz = Console.ReadLine();

            //provjeravamo da li niz sadr�ava znakove iz abecede {0,1,2}

            for (int i = 0; i < ulaz.Length; i++)
            {
                if (ulaz[i] != '0' && ulaz[i] != '1' && ulaz[i] != '2')
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("\nGre�ka: Nije upisan valjani znak");
                    Console.ForegroundColor = ConsoleColor.Gray;
                    Console.WriteLine("\nEnter za izlaz");
                    Console.ReadLine();
                    return 1;
                }
            }

            //pokrenemo automat

            automat.funkcija_prijelaza(ulaz);

            //zavr�en posao

            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine("\nEnter za izlaz");
            Console.ReadLine();
            return 0;
        }
    }

}