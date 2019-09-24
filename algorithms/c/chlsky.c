


void chlsky_nonBlocked(double** A, int n)
{
    
    for (int k = 0; k < n; ++k)
    {
        A[k][k] = sqrt([A[k][k]);
        
        for (int i = k + 1; i < n; ++i)
        {
            A[i][k] = A[i][k] / A[k][k];
        }
        
        for(int j = k + 1; j < n; ++j)
        {
            for (int i = j; i < n; ++i)
            {
                A[i][j] = A[i][j] - A[i][k] * A[j][k];
            }
        }
    }
    
}

void chlsky_Blocked(double** A, int n, int nb)
{
    int N = ciel(n / nb);
    
    for (int k = 0; k < N; k++)
    {            
        int x = nb * k;
        int y = nb * l;
        // Create a new outer array to hold pointers to the element of each inner array
        float** submat = (float **) calloc(nb, sizeof(float*));
        for (int i = 0; i < nb; i++)
        {
            submat[i] = A[y++] + x;
        }
        chlsky_nonBlocked(submat, nb);
    }
}
