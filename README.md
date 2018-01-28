### Zadanie

Napisany został program, którt oblicza  prawdopodobieństwo wygrania gry przez gracza G1, mając dane wejściowe podane w kojenych wierszach: rozmiar planszy, liczę grzybów oraz ich rozmieszczenie, pola startowe obu graczy, liczbę ścian kostki, wartości na ścianach kostki, rozkład kostki.

### Implementacja

Implementacja opiera się o klasę MyMatrix z zadania drugiego, do której strzworzone zostały implmentacje metody Gaussa dla macierzy rzadkich, metody iteracyjne Gaussa-Seidela I Jacobiego.

Do tworzenia macierzy prawdopodobieńst stworzone zostały klasa Generator, która za argument przyjmuje nazwę pliku wejściowego oraz klasa State implementująca stan.

Do symulacji gry ( Metoda Monte-Carlo ) stworzone zostały klasy MonteCarlo, Dice, Field oraz Player.
