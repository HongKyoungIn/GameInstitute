using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    private float moveSpeed = 4f;

    private Vector3 bottomLeft;
    private Vector3 topRight;
    private float worldWidth;
    private float worldHeight;

    private float spawnRate = 0.5f;
    private float timer;
    public GameObject playerBullet;

    private void Start()
    {
        // 월드의 가로와 세로 크기 계산
        bottomLeft = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, 0));
        topRight = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, 0));
        worldWidth = topRight.x - bottomLeft.x;
        worldHeight = topRight.y - bottomLeft.y;
    }

    private void Update()
    {
        PlayerMove();
        AutoBulletShoot();
    }

    private void PlayerMove()
    {
        float horizontalMove = Input.GetAxis("Horizontal");
        float verticalMove = Input.GetAxis("Vertical");

        Vector3 position = transform.position;
        position += new Vector3(horizontalMove, verticalMove, 0f) * moveSpeed * Time.deltaTime;
        position.x = Mathf.Clamp(position.x, bottomLeft.x, topRight.x);
        position.y = Mathf.Clamp(position.y, bottomLeft.y, topRight.y);
        transform.position = position;
    }

    private void AutoBulletShoot()
    {
        timer += Time.deltaTime;

        if(timer > spawnRate)
        {
            timer = 0f;
            if(playerBullet != null)
            {
                Instantiate(playerBullet, transform.position, Quaternion.identity);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("Enemy") || collision.gameObject.CompareTag("EnemyBullet"))
        {
            Debug.Log("Scene Load");
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}