using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class NumberClick : MonoBehaviour, IPointerDownHandler
{
    public int index;
    [SerializeField] SearchController searchController;
    public void OnPointerDown(PointerEventData eventData)
    {
        searchController.numberClick(index);
    }
}
