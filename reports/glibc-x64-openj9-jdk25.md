---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:14:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1794319750 85
1794319755 85
1794319760 85
1794319765 88
1794319770 88
1794319775 88
1794319780 88
1794319785 88
1794319790 88
1794319795 88
1794319800 88
1794319805 88
1794319810 88
1794319815 96
1794319820 96
1794319825 96
1794319830 96
1794319835 96
1794319840 96
1794319845 96
```
</details>

---

