echo building training app ...
g++ src/main.cpp -I ./src -o A-Croak

echo building similarity ...
g++ src/similarity.cpp -I ./src -o similarity

echo try running_example.sh to train word vectors
