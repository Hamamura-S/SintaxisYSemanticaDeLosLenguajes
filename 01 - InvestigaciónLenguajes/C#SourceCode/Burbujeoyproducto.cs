using System;
using System.Diagnostics;

namespace sintaxis
{
    class Program
    {
        static void Main(string[] args)
        {
            /* Producto entre matrices 3x3*/
            int[,] Matriz_uno = { {9,7,1}, {8,4,7}, {7,4,5}};
            int[,] Matriz_dos = { {6,7,6}, {5,9,15}, {4,74,23}};

            int[,] Matriz_producto = new int[3,3];

            var cronometro = Stopwatch.StartNew();

            for (int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {

                    for(int k = 0; k < 3; k++)
                    {
                        Matriz_producto[i,j] += Matriz_uno[k,j]* Matriz_dos[j,k];
                    }

                }
            }

            cronometro.Stop(); 

            Console.WriteLine($"Tardado de multiplicación de matriz: {cronometro.Elapsed.TotalMilliseconds*1000000}");


            /*Ordenamiento burbujeo*/
            int[] numeros = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

            int auxiliar = 0;

            var otro_cronometro = Stopwatch.StartNew();

            for (int i = 0; i < numeros.Length; i++)
            {
                for (int j = 0; j < numeros.Length - 1; j++)
                {
                    if (numeros[j] > numeros[j + 1])
                    {
                        auxiliar = numeros[j];
                        numeros[j] = numeros[j + 1];
                        numeros[j + 1] = auxiliar;
                    }
                }
            }

            otro_cronometro.Stop();
            Console.WriteLine($"Tardado de burbujeo: {otro_cronometro.Elapsed.TotalMilliseconds*1000000}");

        }
    }
}
