#include "jogovelha.h"

JogoVelha::JogoVelha(): tab(9)
{
  reiniciar();
}

void JogoVelha::reiniciar()
{
  for (int i=0; i<3; i++) for (int j=0; j<3; j++)
  {
    set(i,j) = ' ';  // Espaco = casa vazia;
  }
  vez = 'X'; // Sempre comeca com o jogador X
  venc = ' '; // Nenhum vencedor
}

// Retorna true se alguem ganhou
// Se teste for positivo, altera venc e vez <- ' '
bool JogoVelha::vitoria()
{
  for (int k=0; k<3; k++)
  {
    // Testa as linhas
    if ((at(k,0)=='X' || at(k,0)=='O') &&
        at(k,1)==at(k,0) && at(k,2)==at(k,0) )
    {
      venc = at(k,0);
      vez = ' ';
      return true;
    }
    // Testa as colunas
    if ((at(0,k)=='X' || at(0,k)=='O') &&
        at(1,k)==at(0,k) && at(2,k)==at(0,k) )
    {
      venc = at(0,k);
      vez = ' ';
      return true;
    }
  }
  // Testa as diagonais
  if ((at(1,1)=='X' || at(1,1)=='O') &&
      ( (at(0,0)==at(1,1) && at(2,2)==at(1,1)) ||
        (at(0,2)==at(1,1) && at(2,0)==at(1,1)) ))
  {
    venc = at(1,1);
    vez = ' ';
    return true;
  }
  // Ninguem venceu
  return false;
}

// Retorna true se nao pode mais ganhar
// (vitoria ou tabuleiro completo)
// Se teste for positivo, vez <- ' '
bool JogoVelha::fimDeJogo()
{
  // Alguem jah ganhou o jogo?
  if (venc == ' ')
  {
    for (int i=0; i<3; i++) for (int j=0; j<3; j++)
    {
      if (at(i,j) == ' ') return false;
    }
  }
  // Jogo acabou: nao tem mais jogador valido
  vez = ' ';
  return true;
}

// Testa se o jogador da vez pode jogar na casa <I,J>
bool JogoVelha::jogadaValida(int I, int J) const
{
  // Alguem jah ganhou o jogo?
  if (venc != ' ') return false;
  // Tem um jogador apto a jogar?
  if (vez!='X' && vez!='O') return false;
  // Checa os indices
  if (I<0 || I>=3 || J<0 || J>=3) return false;
  // Checa se a casa estah vazia
  if (at(I,J) != ' ') return false;

  // Jogada eh valida
  return true;
}

// Coloca a marca do jogador da vez na casa <I,J>
void JogoVelha::fazerJogada(int I, int J)
{
  if (jogadaValida(I,J))
  {
    set(I,J) = vez;
  }
  // Testa se ganhou o jogo
  if (!vitoria() && !fimDeJogo())
  {
    vez = (vez=='O' ? 'X' : 'O');
  }
}
