// Vorzeichenlose ganze Zahl.
using uint = unsigned int;

// Mit Verkettung implementierte Streuwerttabelle
// mit SchlÃ¼sseltyp K und Werttyp V.
// An der Stelle, an der HashChain fÃ¼r einen bestimmten SchlÃ¼sseltyp K
// verwendet wird, muss eine Funktion uint hashval (K) zur Berechnung
// von Streuwerten sowie ein passender Gleichheitsoperator (==) fÃ¼r den
// Typ K bekannt sein.
template <typename K, typename V>
struct HashChain {
    // Initialisierung mit GrÃ¶ÃŸe n.
    HashChain (uint n)

    // Eintrag mit SchlÃ¼ssel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufÃ¼gen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put (K k, V v)

    // Wert zum SchlÃ¼ssel k Ã¼ber den Referenzparameter v zurÃ¼ckliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unverÃ¤ndert, und der Resultatwert ist false.
    bool get (K k, V& v)

    // Eintrag mit SchlÃ¼ssel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove (K k)

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // SchlÃ¼ssel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere PlÃ¤tze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // fÃ¼r die Typen K und V geben.
    void dump ()
};

// Sondierungssequenz mit SchlÃ¼sseltyp K fÃ¼r lineare Sondierung.
// An der Stelle, an der LinProb fÃ¼r einen bestimmten SchlÃ¼sseltyp K
// verwendet wird, muss wiederum uint hashval (K) bekannt sein.
template <typename K>
struct LinProb {
    // Initialisierung der Sequenz mit SchlÃ¼ssel k und TabellengrÃ¶ÃŸe n.
    LinProb (K k, uint n)

    // Den ersten bzw. nÃ¤chsten Wert der Sequenz liefern.
    // Nach einem Aufruf des Konstruktors darf diese Funktion also
    // bis zu n-mal aufgerufen werden.
    // Achtung: Die direkte Verwendung der Formel
    // s[j](k) = (h(k) + j) mod n
    // kann durch arithmetischen Ãœberlauf zu falschen Ergebnissen
    // fÃ¼hren, wenn h(k) sehr groÃŸ ist.
    // Deshalb sollte nur der erste Wert s[0](k) = h(k) mod n direkt
    // und alle weiteren Werte jeweils aus dem vorigen Wert berechnet
    // werden: s[j](k) = (s[j-1](k) + 1) mod n fÃ¼r j = 1, ..., n-1.
    // Der vorige Wert kann hierfÃ¼r in einer Elementvariablen
    // gespeichert werden.
    // Dann kann bei realistischen TabellengrÃ¶ÃŸen n kein Ãœberlauf
    // auftreten.
    uint next ()
};

// Sondierungssequenz mit SchlÃ¼sseltyp K fÃ¼r quadratische Sondierung,
// analog zu LinProb.
template <typename K>
struct QuadProb {
};

// Sondierungssequenz mit SchlÃ¼sseltyp K fÃ¼r doppelte Streuung.
// An der Stelle, an der DblHash fÃ¼r einen bestimmten SchlÃ¼sseltyp K
// verwendet wird, muss wiederum uint hashval (K) sowie eine zweite
// Streuwertfunktion uint hashval2 (K, uint n) bekannt sein, die nur
// Werte von 1 bis n - 1 liefert, die teilerfremd zu n sind.
// Ansonsten analog zu LinProb.
template <typename K>
struct DblHash {
};

// Mit offener Adressierung implementierte Streuwerttabelle mit
// SchlÃ¼sseltyp K, Werttyp V und Sondierungssequenz des Typs S.
// S muss einen Konstruktor S (K, uint) zur Initialisierung der Sequenz
// sowie eine Elementfunktion next () zur Abfrage des ersten bzw.
// nÃ¤chsten Werts der Sequenz besitzen.
// Bedeutung von Konstruktor und Elementfunktionen wie bei HashChain
// mit folgenden Ã„nderungen:
// put ist bei einer vollen Tabelle wirkungslos und liefert false,
// wenn ein neuer Eintrag hinzugefÃ¼gt werden mÃ¼sste.
// dump gibt von PlÃ¤tzen mit LÃ¶schmarkierung nur ihre Nummer aus.
template <typename K, typename V, typename S>
struct HashOpen {
};//
// Created by Lucas Noki on 29.10.21.
//

#ifndef ALGO2_A1_HASHING_H
#define ALGO2_A1_HASHING_H

#endif //ALGO2_A1_HASHING_H
