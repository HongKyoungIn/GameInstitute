using System.Collections;
using UnityEngine;

// 플레이어 방향으로bulletSetCount 개수 만큼  발사체 생성  
public class EnemyBulletFire3 : MonoBehaviour
{
    public GameObject bulletPrefab;

    private float angleInterval;
    private float spawnWait = 2f;
    private int bulletSetCount;

    private void Start()
    {
        angleInterval = 20.0f;
        bulletSetCount = 7;
        StartCoroutine(FireBullets());
    }

    private IEnumerator FireBullets()
    {
        yield return new WaitForSeconds(1.0f);

        while (true)
        {
            for (int i = 0; i < bulletSetCount; i++)
            {
                float startAngle = transform.eulerAngles.z - 45;
                float endAngle = transform.eulerAngles.z + 45;
                float angleInterval = (endAngle - startAngle) / (bulletSetCount - 1);

                float angle = startAngle + i * angleInterval;
                GameObject bullet = Instantiate(bulletPrefab, transform.position, Quaternion.identity);
                float cos = Mathf.Cos(angle * Mathf.Deg2Rad);
                float sin = Mathf.Sin(angle * Mathf.Deg2Rad);
                bullet.GetComponent<EnemyBullet>().moveDirection = new Vector3(cos, sin, 0); ;
                bullet.transform.rotation = Quaternion.Euler(0, 0, 90 + angle);
            }
            yield return new WaitForSeconds(spawnWait);
        }
    }
}