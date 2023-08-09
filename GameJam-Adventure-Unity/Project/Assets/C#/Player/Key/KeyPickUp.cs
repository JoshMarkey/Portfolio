using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class KeyPickUp : MonoBehaviour, IPointerDownHandler, IBeginDragHandler, IEndDragHandler, IDragHandler
{

    private RectTransform rect;
    public CanvasGroup canvasGroup;
    public int index;
    [SerializeField] Transform startPos;
    public bool placed;

    private void Start()
    {
        placed = false;
    }

    public void reSetPos()
    {
        transform.position = startPos.position;
    }

    private void Awake()
    {
        rect = GetComponent<RectTransform>();
        canvasGroup = GetComponent<CanvasGroup>();
    }

    public void OnBeginDrag(PointerEventData eventData)
    {
        if (!placed)
        {
            canvasGroup.blocksRaycasts = false;
            canvasGroup.alpha = 0.7f;
        }
    }

    public void OnDrag(PointerEventData eventData)
    {
        if (!placed)
        {
            rect.anchoredPosition += eventData.delta;
        }
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        if (!placed)
        {
            canvasGroup.blocksRaycasts = true;
            canvasGroup.alpha = 1f;
        }
    }

    public void OnPointerDown(PointerEventData eventData)
    {

    }
}
