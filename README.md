# 🧠 Philosophers

Ce projet est une implémentation du problème classique des **philosophes** mangeurs, utilisant des **threads (pthreads)** et des **mutex** pour la synchronisation.

## 🧾 Objectif

Simuler le comportement de plusieurs philosophes assis autour d'une table :

* Chaque philosophe alterne entre **penser**, **manger**, et **dormir**.
* Pour manger, un philosophe a besoin de **deux fourchettes** (partagées avec ses voisins).
* Le programme gère la **concurrence**, **la synchronisation**, et évite les **deadlocks** et **starvations**.

## ⚙️ Compilation

```bash
make
```

## ▶️ Exécution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Exemple :

```bash
./philo 5 800 200 200
```

* **5** philosophes
* Chaque philosophe meurt s’il ne mange pas pendant **800 ms**
* Il met **200 ms** à manger, puis **200 ms** à dormir

## 🧵 Détails techniques

* Utilise `pthread` pour créer un thread par philosophe
* `mutex` pour protéger l’accès aux fourchettes et à l'affichage (`write_mutex`)
* Synchronisation précise via `precise_usleep()`
* Gestion des morts et de la fin de la simulation

## 📁 Structure

* `philo.c` : boucle principale des philosophes
* `init.c` : initialisation de la table et des philosophes
* `utils/` : fonctions utilitaires (temps, affichage, etc.)
* `monitor.c` : vérifie si un philosophe est mort

## 🧑‍💻 Auteur

* [Bilscript](https://github.com/Bilscript)
