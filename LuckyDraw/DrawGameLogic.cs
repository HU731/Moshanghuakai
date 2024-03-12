public class DrawGameLogic : MonoBehaviour
{
    private PRDManager prdManager;
    private void Start()
    {
        prdManager = GetComponent<PRDManager>();
        if (prdManager == null)
        {
            prdManager = gameObject.AddComponent<PRDManager>();
        }
        // 假设100100是玩家ID
        prdManager.RegisterPlayer(100100);
    }

    public void PlayerAttack(int playerId)
    {
        bool isCrit = prdManager.TryCrit(playerId);
        if (isCrit)
        {
            Debug.Log("暴击!");
        }
        else
        {
            Debug.Log("普通攻击");
        }
    }
}
