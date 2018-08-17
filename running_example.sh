#Training file: text
#Lexicon: lexicon
#Ngram: 3 (trigram)
#Hidden layer dimension: 16
#Learning rate: 0.5

#Target word: love

#Train model
./A-Croak text lexicon 3 16 0.5

#Find similarity of word "love"
./similarity model lexicon << eof
love
eof
