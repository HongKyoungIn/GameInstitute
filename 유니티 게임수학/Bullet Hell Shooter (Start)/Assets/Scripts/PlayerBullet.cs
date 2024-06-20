using UnityEngine;

public class PlayerBullet : MonoBehaviour
{
    public float moveSpeed = 8f;

    private void Update()
    {
        Vector3 viewportPosition = Camera.main.WorldToViewportPoint(transform.position);
        if (viewportPosition.y > 1)
            GetComponent<Rigidbody2D>().velocity = Vector3.zero; 
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("EnemyBullet")) {
            Destroy(collision.gameObject);
            this.gameObject.SetActive(false);
        } else if (collision.gameObject.CompareTag("Enemy")) {
            Enemy enemyScript = collision.gameObject.GetComponent<Enemy>();
            enemyScript.Damage();
            this.gameObject.SetActive(false);
        }
    }
}