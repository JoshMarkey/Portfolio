using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using DG.Tweening;

public class Hexagon : MonoBehaviour, IPointerClickHandler
{
    public int position;
    public int finalPosition;
    public bool completed = false;
    [SerializeField] HexPuzzleController controller;
    [SerializeField] AudioSource turnSound;
    public Image sprite;
    bool turning = false;
    public float rotationTime;


    public void OnPointerClick(PointerEventData eventData)
    {
        if (completed == false && turning == false)
        {
            turnSound.Play();
            transform.DORotate(new Vector3(0, 0, transform.localEulerAngles.z - 60), rotationTime);
            StartCoroutine(turn());
            //transform.Rotate(new Vector3(0f, 0f, -1f), 60f);
            position++;
            if (position > 5)
            {
                position = 0;
            }
            controller.checkCompletion();
        }
    }

    IEnumerator turn()
    {
        turning = true;
        yield return new WaitForSeconds(rotationTime);
        turning = false;
    }

    private void Start()
    {
        position = Random.Range(0, 5);
        transform.Rotate(new Vector3(0f, 0f, -1f), 60f * position);
    }

    public bool checkPosition()
    {
        if (position == finalPosition)
            return true;
        return false;
    }
}
