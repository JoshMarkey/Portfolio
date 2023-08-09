using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class SlideyTile : MonoBehaviour, IPointerClickHandler
{
    public Image img;
    int correctPosition;
    SlideyController controller;

    public void initalize(Sprite sprite,int i,SlideyController c)
    {
        img.sprite = sprite;
        correctPosition= i;
        controller = c;
    }

    public bool checkPosition(int pos)
    {
        if(pos == correctPosition)
        {
            return true;
        }
        return false;
    }

    void IPointerClickHandler.OnPointerClick(PointerEventData eventData)
    {
        controller.click(this,false);
    }
}
