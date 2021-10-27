# DirectoryAnalyzer

Program służy do pobierania zawartości folderu po podanej ścieżce i wyświetlaniu zwartości folderu\
Program umożliwa analizowanie folderu za pomocą kilku wątków

Wymgania do kompilacji projektu
cmake w wersji 3.8 lub wyższej
kompilator c++, który skompluje pliki w standardzie c++20
bilbioteki google testów

## Instrukcja zbuildowania plkiów źródłowych za pomocą cmake

* Za pomocą terminala wejść do folderu build
* wywołać komendę cmake ..
* wywołać komendę cmake --build .

Po tych krokach powiny się pojawić pliki wykonywalne

* DirectoryAnalyzer właściwy program 
* DirectoryAnalyzerUnitTests program do wywołania testów jednostkowych