#include "minishell.h"

static void sigint_handler_parent(int sig)
{
    (void)sig;
    write(1, "\n", 1);  // Apenas para fornecer uma nova linha, assim como em outras funções
}

void execute_command(t_mini *ms, t_token *cmd)
{
    pid_t pid;
    int status;

    if (!cmd || !cmd->cmd)
        return;

    pid = fork();
    if (pid == 0)  // Processo filho
    {
        signal(SIGINT, SIG_DFL);  // Restaurar comportamento padrão para SIGINT
        signal(SIGQUIT, SIG_DFL); // Restaurar comportamento padrão para SIGQUIT

        execvp(cmd->cmd, cmd->args_file); // Tentar executar o comando

        // Se execvp falhar
        exit(127); // Código de erro 127 para falha no execve
    }
    else if (pid > 0) // Processo pai
    {
        // Adicionar tratamento para SIGINT no processo pai (para quando o Ctrl+C é pressionado)
        signal(SIGINT, sigint_handler_parent);  // Tratar SIGINT no pai

        waitpid(pid, &status, 0); // Esperar pelo filho

        // Se o processo filho terminou normalmente
        if (WIFEXITED(status))
        {
            ms->exit_status = WEXITSTATUS(status); // Captura o código de saída do filho
        }
        else if (WIFSIGNALED(status)) // Se o processo filho foi finalizado por um sinal
        {
            // Verificar qual sinal terminou o filho
            if (WTERMSIG(status) == SIGINT)
                ms->exit_status = 130; // Código de erro 130 para término por SIGINT (Ctrl+C)
            else if (WTERMSIG(status) == SIGQUIT)
                ms->exit_status = 131; // Código de erro 131 para término por SIGQUIT
            else
                ms->exit_status = 1; // Código genérico para outros sinais
        }
        else
        {
            ms->exit_status = 1; // Código de erro genérico, se não terminou normalmente
        }

        // Restaurar o comportamento do SIGINT para o processo pai depois da execução
        signal(SIGINT, SIG_DFL);
    }
    else // Se fork falhar
    {
        perror("Erro ao criar processo");
        ms->exit_status = 1; // Definir erro se fork falhar
    }
}
