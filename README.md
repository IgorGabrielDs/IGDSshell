# igdsSHELL 💻

Projeto de implementação Shell simples em C, rodando Unix/Linux/MacOS feito como uma atividade para o 3o periodo de faculdade.
Essa atividade foi feita de forma individual por mim, ultilizando em torno de 6 bibliotecas C, além de ter sido feita em 1 semana.

<img width="1374" height="170" alt="image" src="https://github.com/user-attachments/assets/a228e683-7d94-4ff9-96fe-3ef9f1a198fd" />


Esse shell tem implementado nele as seguintes coisas:

- Modo interativo
- Modo batch
- Execução de múltiplos comandos na mesma linha (;)
- Modo de execução sequencial
- Modo de execução paralela
- Pipes (|)
- Redirecionamento de saída (>)
- Redirecionamento de saída com append (>>)
- Redirecionamento de entrada (<)
- Execução de processos em background (&)
- Comando "fg"
- Comando "cd"
- Comando "style"
- Comando "help"
- Comando "exit"


Comandos disponiveis no IGDSshell:
```bash
help — mostra esta lista de comandos
style sequential — define execucao sequencial
style parallel — define execucao paralela

cd <diretorio> — muda o diretorio atual
exit — encerra o shell

fg <id> — traz um job do background para foreground
<comando> & — executa comando em background

<comando1> ; <comando2> — executa multiplos comandos na mesma linha
<comando1> | <comando2> — executa comandos com pipe

<comando> > arquivo — redireciona saida para arquivo
<comando> >> arquivo — adiciona saida ao final do arquivo
<comando> < arquivo — usa arquivo como entrada

<comandos Linux> — executa comandos externos via execvp

```
