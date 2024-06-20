using System.Collections;
using UnityEngine;

// angleInterval �������� �ð� �ݴ� �������� ���������� Bullet ����  
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
            
            // angle�� �������� ��ȯ
            float radian = Mathf.Deg2Rad * angle;

            // moveDirection�� �ð� �ݴ�������� ȸ���ϵ��� ����
            bullet.GetComponent<EnemyBullet>().moveDirection = new Vector3(Mathf.Cos(radian), Mathf.Sin(radian), 0);

            // bullet ȸ�� ����
            bullet.transform.rotation = Quaternion.Euler(0, 0, 90 + angle);

            // ���� ����
            angle = (angle + angleInterval) % 360f;

            yield return new WaitForSeconds(spawnWait);
        }
    }
}