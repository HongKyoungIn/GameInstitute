using UnityEngine;

[RequireComponent(typeof(Rigidbody2D))]
[RequireComponent(typeof(CircleCollider2D))]
public class PlayerBullet : MonoBehaviour
{
    private Vector3 moveDirection = Vector3.right;
    private float moveSpeed = 10f;

    private void Start()
    {
        Rigidbody2D rb2d = GetComponent<Rigidbody2D>();
        rb2d.gravityScale = 0;
        rb2d.velocity = moveDirection * moveSpeed;

        CircleCollider2D collider2D = GetComponent<CircleCollider2D>();
        collider2D.isTrigger = true;
    }

    private void Update()
    {
        Vector3 viewport = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, 0));

        if(transform.position.x > viewport.x)
        {
            Destroy(gameObject);
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("Enemy") || collision.gameObject.CompareTag("EnemyBullet"))
        {
            Destroy(collision.gameObject);
            Destroy(gameObject);
        }
    }
}