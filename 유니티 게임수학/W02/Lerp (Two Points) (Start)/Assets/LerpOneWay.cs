using UnityEngine;

public class LerpOneWay : MonoBehaviour
{
    public Transform[] twoPoints;

    private float duration = 2f;
    private Transform square;
    private float ellipsedTime;
    private float moveSpeed = 2f;

    private void Update() {
        ellipsedTime += Time.deltaTime;

        float t = ellipsedTime / moveSpeed;
        if(t >= 1f) {
            ellipsedTime = 0f;
        }
        transform.position = (1f - t) * twoPoints[0].position + t * twoPoints[1].position;
    }
}