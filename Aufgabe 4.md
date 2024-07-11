### Warum sind die Zugriffe auf das Elternarray ein guter Proxywert?

Die Anzahl der Zugriffe auf das Elternarray ist ein guter Proxywert für die Effizienz der Union-Find-Algorithmen, da diese Zugriffe die grundlegenden Operationen darstellen, die direkt mit der Laufzeit des Algorithmus korrelieren. Wie bei der Analyse von Sortieralgorithmen, bei denen Vergleiche als Proxywert verwendet werden, repräsentieren die Elternarray-Zugriffe die wesentlichen Operationen zur Bestimmung der Effizienz der Union-Find-Algorithmen.

### Beobachtungen aus dem zweiten Plot:

Der zweite Plot zeigt die normalisierten Zugriffe auf das Elternarray. Die Methode mit Union-by-Rank fällt schneller ab als die Methode mit Rangkompression. Beide Methoden fallen schneller als m log(n) ab (keine Konvergenz ersichtlich), was mit der Beschreibung der kombinierten Methode- (besser als naiv, aber noch nicht so gut wie kombiniert -, welche der inversen Ackermannfunktion folgen sollen (sieh VL), übereinstimmt (= schneller als logarithmischer Abfall).
 