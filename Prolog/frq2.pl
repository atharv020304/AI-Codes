happy(ram).
listens2Music(raj).
listens2Music(ram):- happy(ram).
playsAirGuitar(raj):- listens2Music(raj).
playsAirGuitar(ram):- listens2Music(ram).
