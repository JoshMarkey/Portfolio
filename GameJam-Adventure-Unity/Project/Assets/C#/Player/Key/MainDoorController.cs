using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainDoorController : MonoBehaviour
{
    [SerializeField] GameObject unlockText;
    [SerializeField] GameObject backText;
    [SerializeField] GameObject keyPuzzle;
    [SerializeField] SpriteRenderer background;
    [SerializeField] Sprite backgroundDoorOpen;
    [SerializeField] Transform player;
    [SerializeField] List<GameObject> keyParts;
    [SerializeField] AudioSource doorSound;
    public List<bool> keyPartsActive;
    [SerializeField] GameObject battery;
    private bool inRange;
    private bool open;
    public int keysIn;

    private void Start()
    {
        inRange = false;
        open = false;
        keysIn = 0;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            unlockText.SetActive(true);
            inRange = true;
        }
    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        if (open)
        {
            if (collision.CompareTag("Player"))
            {
                unlockText.SetActive(true);
            }
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            unlockText.SetActive(false);
            closePuzzle();
            inRange = false;
        }
    }

    private void Update()
    {
        if (!open)
        {
            if (inRange)
            {
                if (Input.GetKeyDown(KeyCode.E))
                {
                    battery.SetActive(false);
                    keyPuzzle.SetActive(true);
                    backText.SetActive(true);
                    unlockText.SetActive(false);
                    for (int i = 0; i < keyParts.Count; i++)
                    {
                        if (keyPartsActive[i] == true)
                        {
                            keyParts[i].SetActive(true);
                        }
                        else
                        {
                            keyParts[i].SetActive(false);
                        }
                    }
                }
            }
        }
        else
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                SceneManager.LoadScene("Forest1");
            }
        }
        if (keysIn == 4)
        {
            if (!open)
            {
                openDoor();
            }
        }
    }

    public void closePuzzle()
    {
        battery.SetActive(true);
        keyPuzzle.SetActive(false);
        backText.SetActive(false);
    }

    public void openDoor()
    {
        doorSound.Play();
        open = true;
        closePuzzle();
        unlockText.SetActive(true);
        background.sprite = backgroundDoorOpen;
    }
}
