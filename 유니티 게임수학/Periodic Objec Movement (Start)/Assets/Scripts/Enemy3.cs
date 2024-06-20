using UnityEngine;

public class Enemy3 : MonoBehaviour
{
    private Vector3 moveDirection;
    private float moveSpeed = 2f;
    private float frequency = 0.2f;
    private float amplitude = 2.5f;
    private float timerMove;
    private float initialYPosition;

    private float spawnRate = 1f;
    private float timerShoot;
    public GameObject enemyrBullet;

    private void Start()
    {
        Vector3 topRight = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, 0));
        Vector3 spawnPosition = new Vector3(topRight.x, Random.Range(-topRight.y, topRight.y), 0);
        transform.position = spawnPosition;

        moveDirection = Vector3.left;
        initialYPosition = transform.position.y;
    }

    private void Update()
    {
        EnemyMove();
        AutoBulletShoot();
    }
        
    private void EnemyMove()
    {
        Vector3 position = transform.position;
        position += moveDirection * moveSpeed * Time.deltaTime;

        timerMove += Time.deltaTime;
        float sinValue = 0f; 

        position.y = initialYPosition + sinValue;
        transform.position = position;

        Vector3 bottomLeft = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, 0));
        if (transform.position.x < bottomLeft.x)
        {
            Destroy(gameObject);
        }
    }

    private void AutoBulletShoot()
    {
        timerShoot += Time.deltaTime;

        if (timerShoot > spawnRate)
        {
            timerShoot = 0f;
            if (enemyrBullet != null)
            {
                Instantiate(enemyrBullet, transform.position, Quaternion.identity);
            }
        }
    }
}