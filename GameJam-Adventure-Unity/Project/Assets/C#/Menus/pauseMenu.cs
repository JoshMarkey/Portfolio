using UnityEngine;

public class pauseMenu : MonoBehaviour
{

    [SerializeField] GameObject battery;
    [SerializeField] GameObject pausemenu;
    private bool paused;

    private void Awake()
    {
        paused = false;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if(paused)
            {
                Resume();
            }
            else
            {
                pausemenu.SetActive(true);
                battery.SetActive(false);
                paused = true;
                Time.timeScale = 0.0f;
            }
           
        }
    }

    public void exit()
    {
        Application.Quit();
    }

    public void Resume()
    {
        pausemenu.SetActive(false);
        battery.SetActive(true);
        paused = false;
        Time.timeScale = 1.0f;
    }
}
