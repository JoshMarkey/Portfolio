using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ForestSceneController : MonoBehaviour
{
    private void OnTriggerStay2D(Collider2D collision)
    {
        if(collision.CompareTag("Forest1"))
        {
            SceneManager.LoadScene("Forest1");
        }else if(collision.CompareTag("Forest2"))
        {
            SceneManager.LoadScene("Forest2");
        }
        else if (collision.CompareTag("Forest3"))
        {
            SceneManager.LoadScene("Forest3");
        }
        else if (collision.CompareTag("Forest4"))
        {
            SceneManager.LoadScene("Forest4");
        }
        else if (collision.CompareTag("House"))
        {
            SceneManager.LoadScene("StartRoom");
        }
    }
}
