using UnityEngine;

public class LerpPingPongSin : MonoBehaviour
{
    public Transform[] twoPoints;

    private float duration = 2f;
    private Transform square;
    private float ellipsedTime;
    private float moveSpeed = 2f;
    private int sign = 1;
    private float waveFequernce = 5f; // sin ������
    private float waveAmplitude = 1f; // sin ���� 

    private void Update() {
        
    }
}