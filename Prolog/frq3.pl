% Facts
motivated(alex).
motivated(sam).
likesSubject(alex, math).
likesSubject(lisa, science).
attendsClass(sam).
attendsClass(lisa).

% Rules
studies(X) :- motivated(X), attendsClass(X).
studies(X) :- likesSubject(X, _).

getsGoodGrades(X) :- studies(X).
getsScholarship(X) :- getsGoodGrades(X), motivated(X).
