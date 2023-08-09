using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimeClickPuzzle : MonoBehaviour
{
    public Desk1Interaction desk1Interaction;
    [SerializeField] List<Slider> gameSliders;
    [SerializeField] List<float> gameSlidersSpeed;
    [SerializeField] AudioSource CompleteSound;
    [SerializeField] AudioSource PlaceSound;
    private int currentSlider;
    private bool up;
    private bool win;

    private void Start()
    {
        currentSlider = 0;
        up = true;
        win = false;
    }

    void FixedUpdate()
    {
        if (!win)
        {
            //Move squares side to side
            if (gameSliders[currentSlider].value <= 0)
            {
                up = true;
            }
            else if (gameSliders[currentSlider].value >= 10)
            {
                up = false;
            }
            if (up)
            {
                gameSliders[currentSlider].value += gameSlidersSpeed[currentSlider];
            }
            else
            {
                gameSliders[currentSlider].value -= gameSlidersSpeed[currentSlider];
            }
        }
    }

    private void Update()
    {
        if (!win)
        {
            //check for click to drop square
            if (Input.GetKeyDown(KeyCode.Space))
            {
                PlaceSound.Play();
                if (gameSliders[currentSlider].value < 6 && gameSliders[currentSlider].value > 4)
                {
                    if (currentSlider == 5)
                    {
                        //win
                        gameSliders[currentSlider].value = 5;
                        win = true;
                        CompleteSound.Play();
                        StartCoroutine(end());
                    }
                    else
                    {
                        gameSliders[currentSlider].value = 5;
                        currentSlider++;
                        gameSliders[currentSlider].gameObject.SetActive(true);
                    }
                }
                else
                {
                    foreach (Slider slider in gameSliders)
                    {
                        slider.value = 5;
                        slider.gameObject.SetActive(false);
                    }
                    currentSlider = 0;
                    gameSliders[currentSlider].gameObject.SetActive(true);
                }
            }
        }
    }

    IEnumerator end()
    {
        yield return new WaitForSeconds(0.7f);
        desk1Interaction.completePuzzle();
    }
}
