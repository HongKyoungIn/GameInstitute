using UnityEngine;

public class EllipticalMovement : MonoBehaviour {
    private float radiusA = 4f; // 타원의 장축 반지름
    private float radiusB = 2f; // 타원의 단축 반지름
    private Vector3 center = new Vector3(0, 0, 0); // 원의 중심점
    private float rotationFrequency = 0.5f; // 초당 회전 수
    private float ellipsedTime; // 경과 시간

    private void Start() {
        center = transform.position; // 초기 위치를 중심점으로 설정
    }

    private void Update() {
        ellipsedTime += Time.deltaTime; // 경과 시간 업데이트

        float t = ellipsedTime * rotationFrequency; // 회전 각도 계산
        float x = radiusA * Mathf.Cos(t * Mathf.PI * 2); // x 좌표 계산
        float y = radiusB * Mathf.Sin(t * Mathf.PI * 2); // y 좌표 계산
        Vector3 position = new Vector3(x, y, 0); // 새로운 위치 계산
        transform.position = center + position; // 오브젝트 위치 업데이트
    }
}