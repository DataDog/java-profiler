---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:12:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1793185668 52
1793185673 52
1793185678 52
1793185683 52
1793185688 52
1793185693 52
1793185698 52
1793185703 52
1793185708 52
1793185713 52
1793185718 52
1793185723 52
1793185728 52
1793185733 52
1793185738 52
1793185743 52
1793185748 52
1793185753 50
1793185758 50
1793185763 50
```
</details>

---

