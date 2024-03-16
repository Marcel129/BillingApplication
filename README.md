# Opis
Mała, prosta aplikacja służąca do wystawiania rachunków na zakupione towary. 
Do tworzenia plików PDF wykorzystano skład tekstu LATEX. Program przechowuje informacje odnośnie sprzedawanych towarów, klientów oraz historii wystawionych rachunków. Szablon dokumentu przechowywany jest jako osobny plik - w celu jego zmiany nie ma potrzeby ponownej kompilacji programu. Do stworzenia interfejsu graficznego wykorzystano bibliotekę Qt. 

Aplikacja powstała z myślą o użytkowaniu przez osoby mniej techniczne (np. osoby starsze), ale prowadzące własną działalność gospodarczą i potrzebujace wystawiać rachunki, stąd ograniczona ilość funcji i niezwykle prosty interfejs użytkownika. 

Program wyposażono w możliwość zdalnej aktualizacji w razie wprowadzenia zmian/usuwania błędów.

### Przykład wystawionego rachunku
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/8cd6585a-226d-448b-9e41-2f8b5008b912)


# Karty aplikacji
### Karta "Rachunek"
Podstawowa karta służąca do wprowadzenia danych wystawcy i odbiorcy oraz listy zakupionych produktów.
![image](https://github.com/Marcel129/SmallBussinesApplication/assets/62217145/a00cb22d-0c7c-4344-82b9-f7e828caa57d)

### Karta "Kontrahenci"
Aplikacja przechowuje bazę danych kontrahentów. Zakładka ta służy do zarządzania ich danymi (dodawanie, usuwanie, edycja). Istnieje możliwość dodania kilku odbiorców dla jednego nabywcy w np. przypadku, gdy nabywca jest organ władzy samorządowej, a odbiorcą podległa mu instytucja.
![image](https://github.com/Marcel129/SmallBussinesApplication/assets/62217145/10e61e20-bf2e-48df-8348-758078046b6e)

### Karta "Produkty"
Program przechowuje również bazę danych sprzedawanych towarów. Zakładka ta służy do ich edycji.
![image](https://github.com/Marcel129/SmallBussinesApplication/assets/62217145/9e6bccb8-9734-4513-a772-1d2954156a9a)

### Karta "Rejestr"
W zakłądce tej dostępny jest podgląd wystawionych już rachunków oraz w razie potrzeby ich odtworzenie lub usunięcie.
![image](https://github.com/Marcel129/SmallBussinesApplication/assets/62217145/63b44666-42ee-4a0f-8103-a9eb3c5fffa1)

