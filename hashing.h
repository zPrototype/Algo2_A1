// Vorzeichenlose ganze Zahl.
using uint = unsigned int;

// Mit Verkettung implementierte Streuwerttabelle
// mit Schluesseltyp K und Werttyp V.
// An der Stelle, an der HashChain fuer einen bestimmten SchlÃ¼sseltyp K
// verwendet wird, muss eine Funktion uint hashval (K) zur Berechnung
// von Streuwerten sowie ein passender Gleichheitsoperator (==) fuer den
// Typ K bekannt sein.
template <typename K, typename V>
struct HashChain {
    struct Elem {
        K key;
        V val;
        Elem* next;
    };

    uint size;
    Elem** tab;
    // Initialisierung mit GrÃ¶ÃŸe n.
    explicit HashChain (uint n) {
        size = n;
        tab = new Elem* [n] ();
    }

    // Eintrag mit Schluessel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufuegen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put (K k, V v) {
        uint i = hashval(k) % size;
        for (Elem* p = tab[i]; p != nullptr; p = p->next) {
            if (p->key == k) {
                // Do something
                *p = v;
                return true;
            }
        }
        return true;
    }

    // Wert zum Schluessel k ueber den Referenzparameter v zurueckliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unveraendert, und der Resultatwert ist false.
    bool get (K k, V& v) {

    }

    // Eintrag mit Schluessel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove (K k) {

    }

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schluessel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plaetze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // fuer die Typen K und V geben.
    void dump () {
        // Dump table contents
        // Platz Key Value
        // 5 (2,3) "zwei"
    }
};

// Sondierungssequenz mit Schluesseltyp K fÃ¼r lineare Sondierung.
// An der Stelle, an der LinProb fuer einen bestimmten Schluesseltyp K
// verwendet wird, muss wiederum uint hashval (K) bekannt sein.
template <typename K>
struct LinProb {
    // Initialisierung der Sequenz mit Schluessel k und TabellengrÃ¶ÃŸe n.
    LinProb (K k, uint n)

    // Den ersten bzw. naechsten Wert der Sequenz liefern.
    // Nach einem Aufruf des Konstruktors darf diese Funktion also
    // bis zu n-mal aufgerufen werden.
    // Achtung: Die direkte Verwendung der Formel
    // s[j](k) = (h(k) + j) mod n
    // kann durch arithmetischen Ueberlauf zu falschen Ergebnissen
    // fuehren, wenn h(k) sehr gross ist.
    // Deshalb sollte nur der erste Wert s[0](k) = h(k) mod n direkt
    // und alle weiteren Werte jeweils aus dem vorigen Wert berechnet
    // werden: s[j](k) = (s[j-1](k) + 1) mod n fuer j = 1, ..., n-1.
    // Der vorige Wert kann hierfuer in einer Elementvariablen
    // gespeichert werden.
    // Dann kann bei realistischen Tabellengroessen n kein Ueberlauf
    // auftreten.
    uint next ()
};

// Sondierungssequenz mit Schluesseltyp K fuer quadratische Sondierung,
// analog zu LinProb.
template <typename K>
struct QuadProb {
};

// Sondierungssequenz mit Schluesseltyp K fuer doppelte Streuung.
// An der Stelle, an der DblHash fuer einen bestimmten Schluesseltyp K
// verwendet wird, muss wiederum uint hashval (K) sowie eine zweite
// Streuwertfunktion uint hashval2 (K, uint n) bekannt sein, die nur
// Werte von 1 bis n - 1 liefert, die teilerfremd zu n sind.
// Ansonsten analog zu LinProb.
template <typename K>
struct DblHash {
};

// Mit offener Adressierung implementierte Streuwerttabelle mit
// Schluesseltyp K, Werttyp V und Sondierungssequenz des Typs S.
// S muss einen Konstruktor S (K, uint) zur Initialisierung der Sequenz
// sowie eine Elementfunktion next () zur Abfrage des ersten bzw.
// naechsten Werts der Sequenz besitzen.
// Bedeutung von Konstruktor und Elementfunktionen wie bei HashChain
// mit folgenden Aenderungen:
// put ist bei einer vollen Tabelle wirkungslos und liefert false,
// wenn ein neuer Eintrag hinzugefuegt werden muesste.
// dump gibt von Plaetzen mit Laeschmarkierung nur ihre Nummer aus.
template <typename K, typename V, typename S>
struct HashOpen {
};//
// Created by Lucas Noki on 29.10.21.
//

#ifndef ALGO2_A1_HASHING_H
#define ALGO2_A1_HASHING_H

#endif //ALGO2_A1_HASHING_H
