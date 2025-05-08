# ft_traceroute

`ft_traceroute` est une réimplémentation simplifiée de la commande Unix `traceroute`, développée dans le cadre d’un projet d’apprentissage des protocoles réseau bas-niveau. Il permet de suivre le chemin qu’un paquet emprunte jusqu’à sa destination en manipulant directement les paquets IP/ICMP et en analysant les réponses.

## 🎯 Objectifs

- Comprendre le fonctionnement de `traceroute`
- Manipuler les sockets RAW et UDP
- Contrôler le champ TTL (Time To Live) des paquets IP
- Traiter les erreurs ICMP

## 🛠️ Fonctionnalités

- Envoi de paquets UDP avec TTL croissant pour découvrir chaque routeur intermédiaire
- Réception et analyse des messages ICMP de type :
  - **Time Exceeded** (type 11) : routeur intermédiaire
  - **Destination Unreachable** (type 3) : destination atteinte
- Affichage des adresses IP
- Affichage des RTT (Round-Trip Time) pour chaque saut
