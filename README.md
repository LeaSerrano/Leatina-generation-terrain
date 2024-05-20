# Projet 3D

[FR]

Ce projet s'inscrit dans le contexte de la matière projet 3D en M2 IMAGINE. C'est un projet réalisé en binôme, il a été réalisé en c++ avec opengl et QT.

Le but : réaliser un projet de génération de terrain en 3D

Nous avons commencé par générer une carte de bruit de Perlin, à la suite de ça nous avons appliqué cette carte sur un plan 3D, c'est ce qui nous a permis d'avoir des reliefs. Nous avons aussi ajouté de l'illumination de Phong et des textures qui sont différentes en fonction de la hauteur. Nous avons mis en place deux types de caméras : le mode visualisateur et le mode première personne. Le mode visualisateur permet de voir de terrain de loin, on peut le faire tourner et lui appliquer diverses modifications. Nous pouvons charger une carte de Perlin, en générer une nouvelle ou encore la sauvegarder. Aussi, il est possible de dessiner sur la carte de Perlin actuelle afin de diminuer ou augmenter la hauteur là où nous dessinons (on peut modifier la taille du pinceau). On pourra aussi ajouter de l'érosion ce qui va simuler l'effet de gouttes qui seraient tombées sur le terrain et qui l'auraient érodé. Nous pourrons aussi modifier la résolution du terrain et sa plage de hauteur. Enfin, dans ce mode on va pouvoir sélectionner l'endroit où nous allons nous trouver lorsqu'on va lancer l'autre mode de caméra. Dans cet autre mode de caméra, le mode première personne, nous allons pouvoir nous déplacer à travers le terrain. On pourra aussi bouger la caméra.

***

[EN]

This project is part of the 3D project course in the M2 IMAGINE program. It is a project carried out in pairs, implemented in C++ with OpenGL and QT.

The goal : to create a 3D terrain generation project

We began by generating a Perlin noise map, then we applied this map to a 3D plane, which allowed us to create terrain features. We also added Phong illumination and textures that vary based on altitude. We implemented two types of cameras : the viewer mode and the first-person mode. The viewer mode allows us to see the terrain from a distance, rotate it, and apply various modifications. We can load a Perlin map, generate a new one, or save it. Additionally, it is possible to draw on the current Perlin map to decrease or increase the height where we draw (the brush size can be adjusted). We can also add erosion to simulate the effect of drops falling on the terrain and eroding it. We can modify the terrain's resolution and height range. Finally, in this mode, we can select the location where we will be positioned when we switch to the other camera mode. In this other camera mode, the first-person mode, we can move through the terrain and move the camera.

https://github.com/LeaSerrano/Leatina-generation-terrain/assets/113998552/dd93776b-a5a8-4be9-84aa-92469980690f
