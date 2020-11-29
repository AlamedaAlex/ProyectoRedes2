''' 
Autor: Alexis Yael Hernández Grimaldo
Varsión Python: 3.7.3
Requerimientos:
    1- Instalar OpenCV con el comando -> pip3 install opencv-contrib-python
'''

from threading import Thread, enumerate
import logging
import cv2
import numpy as np

# Permite vizualizar que hace internamente el hilo
logging.basicConfig(
    level=logging.DEBUG,
    format='[%(levelname)s] (%(threadName)-10s) %(message)s',
)


# Creo la clase hilo que hereda de Thread que es la clase principal de Hilos el python
class Hilo(Thread):
    imagenes = ["avatar.jpg", "escom.png", "LOL.jpg", "xbox.jpeg", "ps5.jpg", "python.png", "c++.png",
                "teams.png","google.png","bootstrap.png","playstore.jpg"]
    carpeta = ["avatar", "escom", "LOL", "xbox", "ps5", "python",
               "c++", "teams", "google", "bootstrap", "playstore"]

    # Defino todos los argumentos
    def __init__(self, args=(), imagen=None, group=None, target=None, name=None, *, daemon=None):
        super().__init__(group=group, target=target, name=name, daemon=daemon)
        self.num_hilo = args
        # imagen_B permitira abir la imagen para despues ser modificada en B del segmento RGB
        self.imagen_B = cv2.imread(
            str(self.carpeta[self.num_hilo])+'/'+str(self.imagenes[self.num_hilo]), cv2.IMREAD_COLOR)
        # imagen_G permitira abir la imagen para despues ser modificada en G del segmento RGB
        self.imagen_G = cv2.imread(
            str(self.carpeta[self.num_hilo])+'/'+str(self.imagenes[self.num_hilo]), cv2.IMREAD_COLOR)
        # imagen_R permitira abir la imagen para despues ser modificada en R del segmento RGB
        self.imagen_R = cv2.imread(
            str(self.carpeta[self.num_hilo])+'/'+str(self.imagenes[self.num_hilo]), cv2.IMREAD_COLOR)

    def run(self):
        # Variables que permiten obtener el alto y ancho de la imagen
        height, width, channels = self.imagen_B.shape
        # Con debug muestro que se esta ejecutando el hilo
        logging.debug("Ejecutando hilo "+str(self.num_hilo))
        # for que permite cambiar todo el segmento B en 255
        for x in range(1, height):
            for y in range(1, width):
                self.imagen_B[x, y][0] = 255
                pixel = self.imagen_B[x, y]
        # for que permite cambiar todo el segmento G en 255
        for x in range(1, height):
            for y in range(1, width):
                self.imagen_G[x, y][1] = 255
                pixel = self.imagen_G[x, y]
        # for que permite cambiar todo el segmento R en 255
        for x in range(1, height):
            for y in range(1, width):
                self.imagen_R[x, y][2] = 255
                pixel = self.imagen_R[x, y]
        # Guardo la imagen modificada del segmento B
        cv2.imwrite(self.carpeta[self.num_hilo]+'/'+self.imagenes[self.num_hilo] +
                    '_B_.jpg', self.imagen_B)
        # Guardo la imagen modificada del segmento G
        cv2.imwrite(self.carpeta[self.num_hilo]+'/'+self.imagenes[self.num_hilo] +
                    '_G_.jpg', self.imagen_G)
        # Guardo la imagen modificada del segmento R
        cv2.imwrite(self.carpeta[self.num_hilo]+'/'+self.imagenes[self.num_hilo] +
                    '_R_.jpg', self.imagen_R)


# Arreglo donde de almacenaran todos los hilos
threads = []
for i in range(11):
    hilo_t = Hilo(args=(i))
    threads.append(hilo_t)
    # Función que inicializa todos los hilos para que corran el comando run
    hilo_t.start()
for i in range(11):
    # Hago que esperen todos los hilos al hilo principal
    threads[i].join()
