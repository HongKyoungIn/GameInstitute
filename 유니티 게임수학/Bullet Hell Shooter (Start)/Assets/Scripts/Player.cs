using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    private float moveSpeed;

    private void Start()
    {
        moveSpeed = 4f;
    }

    private void Update()
    {
        PlayerMovement();
    }

    private void PlayerMovement()
    {
        float horizontalMove = Input.GetAxisRaw("Horizontal");
        float verticalMove = Input.GetAxisRaw("Vertical");
        transform.position += new Vector3(horizontalMove, verticalMove, 0) * moveSpeed * Time.deltaTime;

        Vector3 viewportPosition = Camera.main.WorldToViewportPoint(transform.position);
        viewportPosition.x = Mathf.Clamp01(viewportPosition.x);
        viewportPosition.y = Mathf.Clamp01(viewportPosition.y);
        transform.position = Camera.main.ViewportToWorldPoint(viewportPosition);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("EnemyBullet"))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}