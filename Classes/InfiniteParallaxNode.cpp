#include "InfiniteParallaxNode.h"


InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();
	if (node)
	{
		node->autorelease();
	}
	else
	{
		delete node;
		node = 0;
	}
	return node;
}

void InfiniteParallaxNode::updatePosition()
{
	int safeOffset = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	// 1. Duyệt các con của chuỗi parallax

	for (int i = 0; i < _children.size(); i++)
	{
		auto node = _children.at(i); // Node i
									 // 2. Kiểm tra node đó có ra ngoài màn hình ko, convertToWorldSpace bạn tham khảo tại đây http://www.cocos2d-x.org/wiki/Coordinate_System.
		if (convertToWorldSpace(node->getPosition()).x + node->getContentSize().width * (visibleSize.width / node->getContentSize().width) < safeOffset) // Dùng cho node có AnchorPoint(0,0)
		//if (convertToWorldSpace(node->getPosition()).x + node->getContentSize().width/2 * (visibleSize.width / node->getContentSize().width) < safeOffset) // Dùng cho node có AnchorPoint(0.5,y)
			// 3. Tìm PointObject tương ứng với node hiện tại
			for (int j = 0; j < _parallaxArray->num; j++)
			{
				auto po = (PointObject*)_parallaxArray->arr[j];
				// Nếu có thì tăng thêm độ lệch ra thêm 1 màn hình, tức xuất hiện lại thêm lần nữa
				if (po->getChild() == node)

					if (node->getContentSize().width<visibleSize.width)
					{
						po->setOffset(po->getOffset() + Point(visibleSize.width + node->getContentSize().width * node->getScale(), 0));

					}
					else {
						// Mục đích chỗ này áp dụng cho với những đối tượng có chiều rộng > màn hình sẽ di chuyển đúng 
						po->setOffset(po->getOffset() + Point(node->getContentSize().width*2*node->getScale(),0));
					}
			}
	}
}
