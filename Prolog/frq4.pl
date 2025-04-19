excited(sita).
watchesMovies(geeta).

watchesMovies(sita):- excited(sita).
makesPopcorn(geeta):- watchesMovies(geeta).
makesPopcorn(sita):- watchesMovies(sita).
