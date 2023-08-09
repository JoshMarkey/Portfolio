using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CellDoorController : MonoBehaviour
{

    [SerializeField] GameObject unlockText;
    [SerializeField] GameObject backText;
    [SerializeField] GameObject hexPuzzle;
    [SerializeField] SpriteRenderer background;
    [SerializeField] Sprite backgroundCellOpen;
    [SerializeField] Transform otherSideDoorPos;
    [SerializeField] Transform sideDoorPos;
    [SerializeField] Transform player;
    [SerializeField] AudioSource doorSound;
    private bool inRange;
    private bool open;
    private bool otherSide;

    private void Start()
    {
        inRange = false;
        open = false;
        otherSide = false;
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
        if(open)
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
                    hexPuzzle.SetActive(true);
                    backText.SetActive(true);
                    unlockText.SetActive(false);
                }
            }
        }
        else
        {
            if (inRange)
            {
                if (Input.GetKeyDown(KeyCode.E))
                {
                    doorSound.Play();
                    if (!otherSide)
                    {
                        player.position = otherSideDoorPos.position;
                        otherSide = true;
                    }
                    else
                    {
                        player.position = sideDoorPos.position;
                        otherSide = false;
                    }
                }
            }
        }
    }

    public void closePuzzle()
    {
        hexPuzzle.SetActive(false);
        backText.SetActive(false);
    }

    public void openDoor()
    {
        open = true;
        closePuzzle();
        unlockText.SetActive(true);
        background.sprite = backgroundCellOpen;
    }
}
