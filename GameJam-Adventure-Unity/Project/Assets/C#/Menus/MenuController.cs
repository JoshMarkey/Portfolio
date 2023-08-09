using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MenuController : MonoBehaviour
{
    [SerializeField] AudioSource click;
    void Start()
    {
        DontDestroyOnLoad(gameObject);
    }
    public void clickStart()
    {
        click.Play();
        SceneManager.LoadScene("StartRoom");
    }


    public void clickQuit()
    {
        click.Play();
        Application.Quit();
    }
}
