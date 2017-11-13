dealNode = iter
            original_degree = iter.degree
            if rankSet[dealNode.degree] is not None:
                if rankSet[dealNode.degree].data < dealNode.data:
                    result = self.Change_Root(rankSet[dealNode.degree], dealNode)
                else:
                    result = self.Change_Root(dealNode, rankSet[dealNode.degree])
                rankSet[original_degree] = None
                rankSet[result.degree] = result
            else:
                rankSet[original_degree] = dealNode
            iter = iter.right