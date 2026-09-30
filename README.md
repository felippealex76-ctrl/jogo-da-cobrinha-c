# Jogo da Cobrinha em C

Esse é o clássico jogo da cobrinha, feito em linguagem C para rodar direto no terminal do Windows. Escrevi esse projeto para praticar programação e, mais do que isso, para transformar um monte de conceito que a gente estuda solto — vetores, structs, laços, leitura de teclado — em algo que funciona de verdade e ainda é divertido de jogar.

A ideia é a de sempre: você controla uma cobra que anda pelo tabuleiro, come a comida que aparece e vai crescendo. Só que quanto mais ela cresce, mais rápido o jogo fica — e mais difícil é desviar da parede e do próprio corpo.

## Como jogar

- Use as setas do teclado para mudar a direção.
- Cada comida vale 10 pontos e faz a cobra crescer um pouco.
- Encostou na parede ou em você mesmo, acabou.
- No fim de cada partida o jogo pergunta se você quer jogar de novo.

No tabuleiro, a cabeça da cobra aponta para onde ela vai (`>`, `<`, `^`, `v`), o corpo aparece como `o`, a comida como `*` e as bordas como `#`.

## O recorde fica salvo

A sua melhor pontuação é guardada em um arquivo chamado `recorde.txt`, criado na mesma pasta do jogo. Assim, mesmo que você feche tudo e volte outro dia, o recorde continua lá — de preferência para ser batido.

## Como rodar

O jogo usa recursos próprios do Windows (`windows.h` e `conio.h`) para ler as setas em tempo real e atualizar a tela, então ele foi pensado para o terminal do Windows.

Se você usa o CLion ou outro editor com suporte a CMake, é só abrir a pasta e mandar rodar. Pelo terminal, com o GCC instalado, dá para compilar assim:

```
gcc main.c -o cobrinha
cobrinha
```

## Sobre como foi feito

Tentei quebrar o jogo em funções pequenas, cada uma responsável por uma coisa só: uma sorteia a comida, outra move a cobra, outra desenha o tabuleiro, outra lê a tecla pressionada. Isso deixou o código bem mais fácil de acompanhar e de mexer quando eu queria mudar alguma coisa — como a velocidade, que vai subindo conforme a cobra aumenta.

É um projeto pequeno, mas que me ajudou bastante a pensar antes de sair escrevendo código e a organizar as ideias em partes que conversam entre si.

## Autor

Feito por Alex Vinicius Felippe.

- GitHub: https://github.com/felippealex76-ctrl
- LinkedIn: https://www.linkedin.com/in/alex-felippe-27b1a1262
