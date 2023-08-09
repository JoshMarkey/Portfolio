using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Desk1Interaction : MonoBehaviour
{
    [SerializeField] MainDoorController mainDoorController;
    [SerializeField] GameObject unlockText;
    [SerializeField] GameObject backText;
    [SerializeField] GameObject puzzle;
    [SerializeField] GameObject keyPiece;
    private GameObject currentPuzzle;
    [SerializeField] Transform CanvasParent;
    private bool inRange;
    private bool open;
    private bool created;

    private void Start()
    {
        inRange = false;
        open = false;
        created = false;
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
                    //backText.SetActive(true);
                    unlockText.SetActive(false);
                }
            }
        }
    }

    private void createPuzzle()
    {
        if (!created)
        {
            created = true;
            currentPuzzle = Instantiate(puzzle, new Vector3(0, 0, 0), Quaternion.identity, CanvasParent);
            currentPuzzle.transform.position = CanvasParent.position;
            currentPuzzle.GetComponent<TimeClickPuzzle>().desk1Interaction = this;
        }
    }

    public void closePuzzle()
    {
        created = false;
        Destroy(currentPuzzle);
        backText.SetActive(false);
    }

    public void completePuzzle()
    {
        open = true;
        mainDoorController.keyPartsActive[1] = true;
        closePuzzle();
        unlockText.SetActive(false);
        keyPiece.SetActive(false);
    }
}
