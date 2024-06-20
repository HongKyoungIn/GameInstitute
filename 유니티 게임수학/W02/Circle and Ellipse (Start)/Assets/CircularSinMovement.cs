using UnityEngine;

public class CircularSinMovement : MonoBehaviour {
    private float radius = 3f; // ���� ������
    private Vector3 center = new Vector3(0, 0, 0); // ���� �߽���
    private float rotationFrequency = 0.5f; // �ʴ� ȸ�� ��
    private float ellipsedTime; // ��� �ð�

    private void Start() {
        center = transform.position; // �ʱ� ��ġ�� �߽������� ����
    }

    private void Update() {
        ellipsedTime += Time.deltaTime; // ��� �ð� ������Ʈ

        float t = ellipsedTime * rotationFrequency; // ȸ�� ���� ���
        float x = radius * Mathf.Cos(t * Mathf.PI * 2); // x ��ǥ ���
        float y = radius * Mathf.Sin(t * Mathf.PI * 2); // y ��ǥ ���
        Vector3 position = new Vector3(x, y, 0); // ���ο� ��ġ ���
        transform.position = center + position; // ������Ʈ ��ġ ������Ʈ
    }
}