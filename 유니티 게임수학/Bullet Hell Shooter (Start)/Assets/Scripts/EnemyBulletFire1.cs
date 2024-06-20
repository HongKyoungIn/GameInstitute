using System.Collections;
using UnityEngine;

// angleInterval 간격으로 시계 반대 방향으로 순차적으로 Bullet 생성  
public class EnemyBulletFire1 : MonoBehaviour
{
    public GameObject bulletPrefab;

    private float angleInterval;
    private float startWait = 1f;
    private float spawnWait = 0.2f;

    private void Start()
    {
        angleInterval = 20.0f;
        StartCoroutine(FireBullets());
    }

    private IEnumerator FireBullets()
    {
        yield return new WaitForSeconds(startWait);

        float angle = 0f;
        while (true)
        {
            GameObject bullet = Instantiate(bulletPrefab, transform.position, Quaternion.identity);
            
            // angle을 라디안으로 변환
            float radian = Mathf.Deg2Rad * angle;

            // moveDirection을 시계 반대방향으로 회전하도록 설정
            bullet.GetComponent<EnemyBullet>().moveDirection = new Vector3(Mathf.Cos(radian), Mathf.Sin(radian), 0);

            // bullet 회전 설정
            bullet.transform.rotation = Quaternion.Euler(0, 0, 90 + angle);

            // 각도 갱신
            angle = (angle + angleInterval) % 360f;

            yield return new WaitForSeconds(spawnWait);
        }
    }
}