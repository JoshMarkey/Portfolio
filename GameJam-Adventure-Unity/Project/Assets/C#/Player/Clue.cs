using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class Clue : MonoBehaviour
{
    [SerializeField] Transform clue1;
    [SerializeField] Transform clue2;
    [SerializeField] Transform clue3;
    [SerializeField] Transform closeButton;
    [SerializeField] AudioSource sound;
    [SerializeField] float duration;
    [SerializeField] PlayerController player;
    Transform clue;
    private Vector3 normalSize = new Vector3(7.41f, 9.27f, 9.27f);
    private Vector3 otherSize = new Vector3(5.14f, 6.87f, 6.87f);
    public bool open = false;
    public void openClue(int num)
    {
        if (!open)
        {
            sound.Play();
            switch (num)
            {
                case 1:
                    clue = clue1;
                    break;
                case 2:
                    clue = clue2;
                    break;
                case 3:
                    clue = clue3;
                    break;
            }
            closeButton.gameObject.SetActive(true);
            clue.gameObject.SetActive(true);
            if (clue == clue2)
            {
                clue.DOScale(otherSize, duration);
            }
            else
            {
                clue.DOScale(normalSize, duration);
            }
            StartCoroutine(delay());
        }
    }

    IEnumerator delay()
    {
        yield return new WaitForSeconds(0.1f);
        open = true;
    }

    private void Update()
    {
        if (open)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                closeClue();
            }
        }
    }


    public void closeClue()
    {
        sound.Play();
        clue.DOScale(new Vector3(0f, 0f, 0f), duration);
        closeButton.gameObject.SetActive(false);
        player.canMove = true;
        open = false;
    }
}
