using UnityEngine;

public class LerpPingPong : MonoBehaviour
{
    public Transform[] twoPoints;

    private float duration = 2f;
    private Transform square;
    private float ellipsedTime;
    private float moveSpeed = 2f;
    private int sign = 1;

    private void Update() {
        ellipsedTime += Time.deltaTime;

        float t = ellipsedTime / moveSpeed;
        if(t >= 1f || t <= 0f) {
            ellipsedTime = 0f;
            sign *= -1;
        }

        t = sign > 0 ? t : (1f - t); 
        transform.position = (1f - t) * twoPoints[0].position + t * twoPoints[1].position;
    }
}