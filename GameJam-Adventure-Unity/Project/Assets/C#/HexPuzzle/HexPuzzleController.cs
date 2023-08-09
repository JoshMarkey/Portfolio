using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HexPuzzleController : MonoBehaviour
{
    [SerializeField] List<Hexagon> hexagons;
    [SerializeField] Sprite winSprite1;
    [SerializeField] Sprite winSprite2;
    [SerializeField] CellDoorController CellDoorController;
    [SerializeField] AudioSource CompleteSound;

    public void checkCompletion()
    {
        StartCoroutine(checkCompletionCo());
    }

    private IEnumerator checkCompletionCo()
    {
        bool check = true;
        foreach (Hexagon hex in hexagons)
        {
            if (hex.checkPosition() != true)
            {
                check = false;
                break;
            }
        }

        if (check)
        {
            GetComponent<Image>().sprite = winSprite2;
            foreach (Hexagon hex in hexagons)
            {
                hex.completed = true;
                hex.sprite.sprite = winSprite1;
            }
            CompleteSound.Play();
            yield return new WaitForSeconds(0.7f);

            CellDoorController.openDoor();
        }
    }
}
