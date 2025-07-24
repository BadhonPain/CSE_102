#include <stdio.h>

int main()
{

  int n, k, I, s, als, ods, evs;
  int fact, sc, en, t_en = 0;

  scanf("%d", &n);

  for (int i = 1; i <= n; i++)
  {

    scanf("%d", &k);

    s = als = ods = evs = 0;

    for (int j = 1; j <= k; j++)
    {

      scanf("%d", &I);
      s = s + I;

      if (j % 2 == 0)
      {

        evs = evs + I;
        als = als - I;
      }
      else
      {

        ods = ods + I;
        als = als + I;
      }
    }

    sc = en = fact = 0;

    for (int c = 1; c <= s; c++)
    {
      if (s % c == 0)
        fact++;
    }
    if (fact == 2)
    {
      en = en + 5;
      sc++;
    }

    int temp = s, rs = 0;
    do
    {
      rs = rs * 10 + s % 10;
      s = s / 10;
    } while (s != 0);

    if (rs == temp)
    {
      en = en + 3;
      sc++;
    }
    if (als % 7 == 0)
    {
      en = en + 4;
      sc++;
    }
    if (evs == ods)
    {
      en = en + 2;
      sc++;
    }

    switch (sc)
    {
    default:
      printf("Row %d :INACTIVE - Energy Level 0\n", i);
      break;

    case 4:
      printf("Row %d :ULTRA - Energy Level %d\n", i, en);
      break;
    case 3:
      printf("Row %d :HIGH - Energy Level %d\n", i, en);
      break;
    case 2:
      printf("Row %d :MEDIUM - Energy Level %d\n", i, en);
      break;
    case 1:
      printf("Row %d :LOW - Energy Level %d\n", i, en);
      break;
    }

    t_en = t_en + en;
  }

  printf("Total Energy : %d", t_en);

  return 0;
}