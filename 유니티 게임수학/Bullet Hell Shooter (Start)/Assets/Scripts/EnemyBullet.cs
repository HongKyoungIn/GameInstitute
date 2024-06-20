using UnityEngine;
using UnityEngine.EventSystems;

public class EnemyBullet : MonoBehaviour
{
    private float moveSpeed = 5f;
    public Vector3 moveDirection = Vector3.right;

    private void Update()
    {
        transform.position += moveDirection * moveSpeed * Time.deltaTime;

        Vector3 viewportPosition = Camera.main.WorldToViewportPoint(transform.position);
        if(viewportPosition.x < 0 || viewportPosition.x > 1)
            Destroy(gameObject);
        if (viewportPosition.y < 0 || viewportPosition.y > 1)
            Destroy(gameObject);
    }
}