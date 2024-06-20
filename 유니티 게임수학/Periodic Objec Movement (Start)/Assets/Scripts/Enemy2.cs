using UnityEngine;
using UnityEngine.UIElements;

public class Enemy2 : MonoBehaviour {
    private float frequency = 0.4f;
    private float radius = 3f;
    private float timerMove;
    private Vector3 initialPosition;
    private Vector3 newPosition;

    private float spawnRate = 1f;
    private float timerShoot;
    public GameObject enemyrBullet;

    private void Start() {
        Vector3 topRight = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, 0));
        float spawnX = Random.Range(3f * topRight.x / 7f, 6f * topRight.x / 7f);
        float spawnY = Random.Range(-topRight.y, topRight.y);
        transform.position = new Vector3(spawnX, spawnY, 0);

        initialPosition = transform.position;
    }

    private void Update() {
        EnemyMove();
        AutoBulletShoot();
    }

    private void EnemyMove() {
        Vector3 position = transform.position;

        timerMove += Time.deltaTime;
        float sinValue = Mathf.Sin(timerMove * frequency * 2 * Mathf.PI);
        float cosValue = Mathf.Cos(timerMove * frequency * 2 * Mathf.PI);

        transform.position = newPosition;
        position.y = initialPosition + sinValue;
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