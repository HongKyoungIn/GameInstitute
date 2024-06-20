using System.Collections;
using UnityEngine;

// angleInterval 간격으로 시계 반대 방향으로 동시에 Bullet 생성  
public class EnemyBulletFire2 : MonoBehaviour
{
    public GameObject bulletPrefab;

    private float angleInterval;
    private float spawnWait = 2f;

    private void Start()
    {
        angleInterval = 20.0f;
        StartCoroutine(FireBullets());
    }

    private IEnumerator FireBullets()
    {
        yield return new WaitForSeconds(1.0f);

        while(true)
        {
            for (int i = 0; i < 360 / angleInterval; i++)
            {
                float angle = i * angleInterval;

                float radian = Mathf.Deg2Rad * angle;

                GameObject bullet = Instantiate(bulletPrefab, transform.position, Quaternion.identity);

                bullet.GetComponent<EnemyBullet>().moveDirection = new Vector3(Mathf.Cos(radian), Mathf.Sin(radian), 0);

                bullet.transform.rotation = Quaternion.Euler(0, 0, 90 + angle);
            }
            yield return new WaitForSeconds(spawnWait);
        }
    }
}