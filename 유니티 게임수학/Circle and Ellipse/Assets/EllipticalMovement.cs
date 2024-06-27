using UnityEngine;

public class EllipticalMovement : MonoBehaviour {
    private float radiusA = 4f; // Ÿ���� ���� ������
    private float radiusB = 2f; // Ÿ���� ���� ������
    private Vector3 center = new Vector3(0, 0, 0); // ���� �߽���
    private float rotationFrequency = 0.5f; // �ʴ� ȸ�� ��
    private float ellipsedTime; // ��� �ð�

    private void Start() {
        center = transform.position; // �ʱ� ��ġ�� �߽������� ����
    }

    private void Update() {
        ellipsedTime += Time.deltaTime; // ��� �ð� ������Ʈ

        float t = ellipsedTime * rotationFrequency; // ȸ�� ���� ���
        float x = radiusA * Mathf.Cos(t * Mathf.PI * 2); // x ��ǥ ���
        float y = radiusB * Mathf.Sin(t * Mathf.PI * 2); // y ��ǥ ���
        Vector3 position = new Vector3(x, y, 0); // ���ο� ��ġ ���
        transform.position = center + position; // ������Ʈ ��ġ ������Ʈ
    }
}