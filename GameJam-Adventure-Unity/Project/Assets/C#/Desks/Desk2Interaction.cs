using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Desk2Interaction : MonoBehaviour
{
    [SerializeField] MainDoorController mainDoorController;
    [SerializeField] GameObject unlockText;
    [SerializeField] GameObject backText;
    [SerializeField] GameObject puzzle;
    [SerializeField] GameObject keyPiece;
    private bool inRange;
    private bool open;

    private void Start()
    {
        inRange = false;
        open = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (!open)
        {
            if (collision.CompareTag("Player"))
            {
                unlockText.SetActive(true);
                inRange = true;
            }
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (!open)
        {
            if (collision.CompareTag("Player"))
            {
                unlockText.SetActive(false);
                closePuzzle();
                inRange = false;
            }
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
                    createPuzzle();
                    backText.SetActive(true);
                    unlockText.SetActive(false);
                }
            }
        }
    }

    private void createPuzzle()
    {
        puzzle.SetActive(true);
    }

    public void closePuzzle()
    {
        puzzle.SetActive(false);
        backText.SetActive(false);
    }

    public void completePuzzle()
    {
        open = true;
        closePuzzle();
        mainDoorController.keyPartsActive[3] = true;
        unlockText.SetActive(false);
        keyPiece.SetActive(false);
    }
}
