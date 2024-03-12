using System.Collections.Generic;
using UnityEngine;

public class PRDManager : MonoBehaviour
{
    private Dictionary<int, double> playerCritChances = new Dictionary<int, double>();
    private double baseC = 0.3; 

    public void RegisterPlayer(int playerId)
    {
        if (!playerCritChances.ContainsKey(playerId))
        {
            playerCritChances[playerId] = 0; 
        }
    }

    public bool TryCrit(int playerId)
    {
        if (!playerCritChances.ContainsKey(playerId)) return false;
        double n = playerCritChances[playerId];
        double p = CalculateCritChance(n);
        bool crit = Random.value < p;
        if (crit)
        {
            playerCritChances[playerId] = 0;
        }
        else
        {
            playerCritChances[playerId] = n + 1;
        }
        return crit;
    }

    private double CalculateCritChance(double n)
    {
        return Mathf.Min(1, (float)(n * baseC));
    }
}
