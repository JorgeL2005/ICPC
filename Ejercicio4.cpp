class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        } // nums1 será más corto

        int n1 = nums1.size();
        int n2 = nums2.size();
        int left = 0, right = n1;

        while (left <= right) {
            // Particion de los arreglos
            int partitionX = (left + right) / 2;
            int partitionY = (n1 + n2 + 1) / 2 - partitionX;
            // Encontramos los 4 numeros necesarios
            int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == n1) ? INT_MAX : nums1[partitionX];
            int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == n2) ? INT_MAX : nums2[partitionY];
    
            // Encontrar la mediana 
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((n1 + n2) % 2 == 0) {
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                } else {
                    return max(maxLeftX, maxLeftY);
                }
            } // Casos en los que la particion no es correcta 
            else if (maxLeftX > minRightY) {
                right = partitionX - 1;
            } else {
                left = partitionX + 1;
            }
        }
        return 0.0;
    }
};
