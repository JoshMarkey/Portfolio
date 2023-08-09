using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class KeyDrop : MonoBehaviour, IDropHandler
{
    [SerializeField] KeyPickUp keyPickUp;
    [SerializeField] int index;
    [SerializeField] AudioSource keySound;
    [SerializeField] MainDoorController MainDoorController;

    public void OnDrop(PointerEventData eventData)
    {
        if (eventData.pointerDrag != null)
        {
            var dropItem = eventData.pointerDrag.GetComponent<KeyPickUp>();
            if (index == dropItem.index) 
            {
                keyPickUp.placed = true;
                MainDoorController.keysIn++;
                eventData.pointerDrag.GetComponent<RectTransform>().anchoredPosition = GetComponent<RectTransform>().anchoredPosition;
                keySound.Play();
            }
            else
            {
                dropItem.reSetPos();
            }
        }
    }
}
