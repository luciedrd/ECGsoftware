# ECGsoftware  

Réalisation avec Qt creator de l'interface graphique d'un électrocardiogramme (exploitation des signaux obtenus avec le microphone de l'odrinateur)

Pour lancer le programme : dans Qt ouvrir tous les documments .cpp et .h du dossier "audiorecorderDardeBensalah". Ensuite lancez "audiorecorder.cpp".

Pour ce projet ma collègue ne parvenait pas à installer Qt creator sur son ordinateur.  
Elle a donc réalisé le rapport et j'ai entièrement programmé ce projet.

Au début de ce projet nous avions des bases de travail :
  
 - audiodevices : un exemple fournit par Qt qui permet de tester les périphériques audio disponibles et leur configuration  
 
 - audiolevel : Permet d’afficher des données audio en temps réel  
 
 - widget : Il permet d’afficher le graphique représentant le signal sonore (l’ECG)  
    Modifications apportées : création des fonctions setStart(), setPause(), setStop() et UpdateTitle() et modification du constructeur avec ajout des lignes 91 à 99 (permant de prendre en entrée un format audio puis d’écrire sur la partie titre les valeurs de max, min et moyenne).  
    
 - xseriesiodevice : Le fichier .h définit le prototype des fonctions. Le fichier .cpp contient l’implémentation des fonctions pour calculer le maximum, le minimum et la moyenne du signal.  
    Modifications apportées : création des fonctions getMin(), getMax() et getMoyenne() et modifications des fonctions  readData() et writeData().  
    
 - formpatient : J'ai créé formpatient.cpp et formpatient.h. Il permet de créer un formulaire pour chaque patient à l'aide d'une nouvelle fenêtre. Le formulaire s'enregistre directement dans l'espace indiqué sous forme de .txt.  
    
 -  audiorecorder.cpp : Ce code affiche une fenêtre permettant à l’utilisateur de sélectionner l’entrée audio, le codec, le conteneur et la fréquence d’échantillonnage appropriés.  
 Modifications apportées : les lignes 146 à 192 ont été ajoutées afin de faire évoluer la fenêtre en y ajoutant widget, xyseriesiodevice, audiolevel et fompatient.
 
 Les explications complémentaires sont dans le document : "audiorecorderDardeBensalah/Projet_DossierC++DardeBensalah.pdf".
