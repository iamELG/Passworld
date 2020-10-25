# Passworld

pour compiler avec clang:
```bash
$ make 
```

pour compiler avec gcc:
```bash
$ make gcc
```

pour executer:
```bash
$ ./main 
```

pour génerer le fichier chiffrer de mot de passe, il faut fair la commande suivant:
```bash
$ openssl enc -e -a -aes-256-cbc -iter 100 -in tmp -out bob.enc
```
par default le nom d'utilisateur est bob,
et le mot de passe est celui definit avec la command openssl(par default le mdp est: azerty)

