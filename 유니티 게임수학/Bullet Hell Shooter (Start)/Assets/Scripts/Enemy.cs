using UnityEngine;
using UnityEngine.SceneManagement;

public class Enemy : MonoBehaviour
{
    public int health;
    private Transform player;
    
    private void Start()
    {
        health = 32;
        player = GameObject.FindGameObjectWithTag("Player").transform;
    }

    private void Update()
    {
        if(health <= 0)
        {
            Destroy(gameObject);
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }

        if(player != null)
        {
            Vector3 lookAtDirection = player.position - transform.position;
            float angle = Mathf.Atan2(lookAtDirection.y, lookAtDirection.x) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle));
        }
    }

    public void Damage()
    {
        health = Mathf.Max(health-1, 0);
    }
}
