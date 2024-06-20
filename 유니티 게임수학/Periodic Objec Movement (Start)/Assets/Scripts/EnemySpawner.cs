using System.Collections;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    private float startWait = 1f;
    private float spawnWait = 1f;

    public GameObject enemy;

    private void Start()
    {
        StartCoroutine("SpwnEnemies");
    }

    private IEnumerator SpwnEnemies()
    {
        yield return new WaitForSeconds(startWait);
        while(true)
        {
            Instantiate(enemy, Vector3.zero, Quaternion.identity);
            yield return new WaitForSeconds(spawnWait);
        }
    }
}