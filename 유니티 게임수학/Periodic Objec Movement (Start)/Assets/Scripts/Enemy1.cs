using UnityEngine;

public class Enemy1 : MonoBehaviour {
    private float frequency = 0.4f;
    private float amplitude = 4f;
    private float timerMove;
    private float initialYPosition;

    private float spawnRate = 1f;
    private float timerShoot;
    public GameObject enemyrBullet;

    private void Start() {
        Vector3 topRight = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, 0));
        float spawnX = Random.Range(3f * topRight.x / 7f, 6f * topRight.x / 7f);
        float spawnY = Random.Range(-topRight.y, topRight.y);
        transform.position = new Vector3(spawnX, spawnY, 0);

        initialYPosition = transform.position.y;
    }

    private void Update() {
        EnemyMove();
        AutoBulletShoot();
    }

    private void EnemyMove() {
        Vector3 position = transform.position;

        timerMove += Time.deltaTime;
        float sinValue = Mathf.Sin(timerMove * frequency * 2 * Mathf.PI) * amplitude;
        position.y = initialYPosition + sinValue;
        transform.position = position;
    }

    private void AutoBulletShoot() {
        timerShoot += Time.deltaTime;

        if (timerShoot > spawnRate) {
            timerShoot = 0f;
            if (enemyrBullet != null) {
                Instantiate(enemyrBullet, transform.position, Quaternion.identity);
            }
        }
    }
}