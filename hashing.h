// Vorzeichenlose ganze Zahl.
using uint = unsigned int;

// Mit Verkettung implementierte Streuwerttabelle
// mit Schluesseltyp K und Werttyp V.
// An der Stelle, an der HashChain fuer einen bestimmten SchlÃ¼sseltyp K
// verwendet wird, muss eine Funktion uint hashval (K) zur Berechnung
// von Streuwerten sowie ein passender Gleichheitsoperator (==) fuer den
// Typ K bekannt sein.
template<typename K, typename V>
struct HashChain
{
    struct Elem
    {
        K key;
        V val;
        Elem *next;
    };

    uint size;
    Elem **tab;

    // Initialisierung mit GrÃ¶ÃŸe n.
    explicit HashChain(uint n)
    {
        size = n;
        tab = new Elem *[n]();
    }

    // Eintrag mit Schluessel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufuegen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put(K k, V v)
    {
        uint idx = hashval(k) % size;
        for (Elem *p = tab[idx]; p != nullptr; p = p->next)
        {
            if (p->key == k)
            {
                p->val = v;
                return true;
            }
        }
        Elem *currentFirstElem = tab[idx];
        Elem *newEntry = new Elem();
        newEntry->key = k;
        newEntry->val = v;
        newEntry->next = currentFirstElem;
        tab[idx] = newEntry;
        return true;
    }

    // Wert zum Schluessel k ueber den Referenzparameter v zurueckliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unveraendert, und der Resultatwert ist false.
    bool get(K k, V &v)
    {
        uint idx = hashval(k) % size;
        if (tab[idx] == nullptr) return false;
        for (Elem *p = tab[idx]; p != nullptr; p = p->next)
        {
            if (p->key == k)
            {
                v = p->val;
                return true;
            }
        }
        return false;
    }

    // Eintrag mit Schluessel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove(K k)
    {
        uint idx = hashval(k) % size;
        Elem *prevElement = nullptr;
        Elem *elem;
        // If element to remove doesn't exist in the first place we return false.
        if (tab[idx] == nullptr) return false;
        // If element exists go through the list until the keys match.
        for (elem = tab[idx]; elem != nullptr; elem = elem->next)
        {
            if (elem->key == k) break;
            // Keep track of the element
            prevElement = elem;
        }
        if (elem == nullptr) return false;
        // If there is no previous element we update the index.
        if (prevElement == nullptr)
        {
            tab[idx] = elem->next;
            // Otherwise we reconnect the previous Element to the next Element to keep the linked list intact.
        } else
        {
            prevElement->next = elem->next;
        }
        return true;
    }

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schluessel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plaetze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // fuer die Typen K und V geben.
    void dump()
    {
        // Dump table contents
        // Platz Key Value
        // 5 (2,3) "zwei"
        for (uint idx = 0; idx < size; idx++)
        {
            for (Elem *p = tab[idx]; p != nullptr; p = p->next)
            {
                cout << idx << " " << p->key << " " << p->val << endl;
            }
        }
    }
};

// Sondierungssequenz mit Schluesseltyp K fuer lineare Sondierung.
// An der Stelle, an der LinProb fuer einen bestimmten Schluesseltyp K
// verwendet wird, muss wiederum uint hashval (K) bekannt sein.
template<typename K>
struct LinProb
{

    uint size;
    K key;
    uint currLinOffset;
    uint initialValue;

    // Initialisierung der Sequenz mit Schluessel k und Tabellengroesse n.
    LinProb(K k, uint n)
    {
        size = n;
        key = k;
        currLinOffset = 0;
        initialValue = n;
    }

    // Den ersten bzw. naechsten Wert der Sequenz liefern.
    // Nach einem Aufruf des Konstruktors darf diese Funktion also
    // bis zu n-mal aufgerufen werden.
    // Achtung: Die direkte Verwendung der Formel
    // subs[j](k) = (h(k) + j) mod n
    // kann durch arithmetischen Ueberlauf zu falschen Ergebnissen
    // fuehren, wenn h(k) sehr gross ist.
    // Deshalb sollte nur der erste Wert subs[0](k) = h(k) mod n direkt
    // und alle weiteren Werte jeweils aus dem vorigen Wert berechnet
    // werden: subs[j](k) = (subs[j-1](k) + 1) mod n fuer j = 1, ..., n-1.
    // Der vorige Wert kann hierfuer in einer Elementvariablen
    // gespeichert werden.
    // Dann kann bei realistischen Tabellengroessen n kein Ueberlauf
    // auftreten.
    uint next()
    {
        if (currLinOffset == size - 1)
        {
            // Crash program because we iterated over the whole hashtable
            return size;
        }
        if (initialValue == size)
        {
            // Cache the first value because of overflowing hash function
            initialValue = hashval(key) % size;
        }

        return (initialValue + currLinOffset++) % size;
    }
};

// Sondierungssequenz mit Schluesseltyp K fuer quadratische Sondierung,
// analog zu LinProb.
template<typename K>
struct QuadProb
{
    uint size;
    K key;
    uint currQuadOffset;
    uint initialValue;

    QuadProb(K k, uint n)
    {
        size = n;
        key = k;
        currQuadOffset = 0;
        initialValue = n;
    }

    uint next()
    {
        if (currQuadOffset == size - 1)
        {
            // Crash programm because of overflowing hash function.
            return size;
        }
        if (initialValue == size)
        {
            initialValue = hashval(key) % size;
        }

        uint newValue = (initialValue + (currQuadOffset + currQuadOffset * currQuadOffset) / 2) % size;
        currQuadOffset++;

        return newValue;
    }
};

// Sondierungssequenz mit Schluesseltyp K fuer doppelte Streuung.
// An der Stelle, an der DblHash fuer einen bestimmten Schluesseltyp K
// verwendet wird, muss wiederum uint hashval (K) sowie eine zweite
// Streuwertfunktion uint hashval2 (K, uint n) bekannt sein, die nur
// Werte von 1 bis n - 1 liefert, die teilerfremd zu n sind.
// Ansonsten analog zu LinProb.
template<typename K>
struct DblHash
{
    uint size;
    K key;
    uint hashcount;

    DblHash(K k, uint n)
    {
        size = n;
        key = k;
        hashcount = 0;
    }

    uint next()
    {
        if (hashcount == size - 1) return size;
        uint hash1 = hashval(key) & size;
        uint hash2 = hashval2(key) % size;
        uint res = (hash1 + hashcount++ * hash2) % size;
        return res;
    }
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
template<typename K, typename V, typename S>
struct HashOpen
{

    struct SimpleElem
    {
        K key;
        V val;
    };

    SimpleElem *TOMBSTONE = new SimpleElem();
    SimpleElem **tab;
    uint size;

    HashOpen(uint n)
    {
        size = n;
        tab = new SimpleElem *[n]();
    }

    bool put(K k, V v)
    {
        S *sondierung = new S(k, size);
        uint pos = sondierung->next();
        SimpleElem *p = tab[pos];
        if (!p)
        {
            // Create new element and add it to tab[pos]
            auto *newElem = new SimpleElem();
            newElem->key = k;
            newElem->val = v;
            tab[pos] = newElem;
            return true;
        }
        do
        {
            if (!p) break;
            if (pos == size) return false;
            if (p == TOMBSTONE) break;
            if (p->key == k)
            {
                p->val = v;
                return true;
            }
            pos = sondierung->next();
            p = tab[pos];
        } while (true);

        auto *newEntry = new SimpleElem();
        newEntry->key = k;
        newEntry->val = v;
        tab[pos] = newEntry;
        return true;
    }

    bool get(K k, V &v)
    {
        S *sondierung = new S(k, size);
        uint pos = sondierung->next();
        SimpleElem *p = tab[pos];
        do
        {
            if (pos == size) return false;
            if (!p) return false;
            if (p->key == k)
            {
                v = p->val;
                return true;
            }
            pos = sondierung->next();
            p = tab[pos];
        } while (true);
    }

    bool remove(K k)
    {
        S *sondierung = new S(k, size);
        uint pos = sondierung->next();
        SimpleElem *p = tab[pos];
        do
        {
            if (pos == size) return false;
            if (!p) return false;
            if (p->key == k)
            {
                tab[pos] = TOMBSTONE;
                return true;
            }
            pos = sondierung->next();
            p = tab[pos];
        } while (true);
    }

    void dump()
    {
        for (uint idx = 0; idx < size; idx++)
        {
            if (!tab[idx]) continue;
            if (tab[idx] == TOMBSTONE)
            {
                cout << idx << endl;
            } else
            {
                cout << idx << " " << tab[idx]->key << " " << tab[idx]->val << endl;
            }
        }
    }
};

//
// Created by Lucas Noki on 29.10.21.
//

#ifndef ALGO2_A1_HASHING_H
#define ALGO2_A1_HASHING_H

#endif //ALGO2_A1_HASHING_H
