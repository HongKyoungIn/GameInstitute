using UnityEngine;

[RequireComponent(typeof(Rigidbody2D))]
[RequireComponent(typeof(CircleCollider2D))]
public class EnemyBulletCahse : MonoBehaviour
{
    private Vector3 moveDirection = Vector3.left;
    private float moveSpeed = 10f;

    private Rigidbody2D rb2d;

    private void Start()
    {
        rb2d = GetComponent<Rigidbody2D>();
        rb2d.gravityScale = 0;

        CircleCollider2D collider2D = GetComponent<CircleCollider2D>();
        collider2D.isTrigger = true;

        GameObject player = GameObject.FindGameObjectWithTag("Player");
        moveDirection = Vector3.left;
        rb2d.velocity = moveDirection * moveSpeed;
    }

    private void Update()
    {

        Vector3 viewport = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, 0));

        if(transform.position.x > viewport.x)
        {
            Destroy(gameObject);
        }
    }
}