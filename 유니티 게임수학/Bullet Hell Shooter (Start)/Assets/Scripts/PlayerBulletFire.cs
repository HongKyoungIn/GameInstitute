using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBulletFire : MonoBehaviour
{
    private bool fireReady = false;
    private float reloadTime = 3f;
    private float reloadTimer;

    public GameObject bulletPrefab;
    public int bulletPoolSize = 8;
    private GameObject[] bullets;
    private Vector3 objectPoolPosition = new Vector3(-10f, -10f, 0f);
    private int currentBullet;

    private bool readyFire = true;

    private void Start()
    {
        fireReady = true;
        bullets = new GameObject[bulletPoolSize];
        for (int i = 0; i < bullets.Length; i++)
        {
            bullets[i] = (GameObject) Instantiate(bulletPrefab, objectPoolPosition, Quaternion.identity);
            bullets[i].GetComponent<Rigidbody2D>().velocity = Vector3.zero;
            bullets[i].SetActive(true);
        }
    }

    private void Update()
    {
        if (Input.GetKey(KeyCode.Space) && readyFire)
        {
            StartCoroutine(FireBullets());
        }

        reloadTimer += Time.deltaTime;
        if(reloadTimer > reloadTime)
        {
            reloadTimer = 0f;
            readyFire = true;
        }
    }

    private IEnumerator FireBullets()
    {
        readyFire = false;
        while (currentBullet < bullets.Length) { 
            bullets[currentBullet].SetActive(true);
            bullets[currentBullet].transform.position = transform.position;
            Vector3 velocity = bullets[currentBullet].GetComponent<PlayerBullet>().moveSpeed * Vector3.up;
            bullets[currentBullet].GetComponent<Rigidbody2D>().velocity = velocity;
            currentBullet++;
            yield return new WaitForSeconds(0.2f);
        }
        currentBullet = 0;
        StopCoroutine(FireBullets());
    }
}