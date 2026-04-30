---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:06:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (6 unique values: 65-89 cores)</summary>

```
1777557731 89
1777557736 89
1777557741 79
1777557746 79
1777557751 79
1777557756 74
1777557761 74
1777557766 74
1777557771 71
1777557776 71
1777557781 69
1777557786 69
1777557791 69
1777557796 69
1777557801 69
1777557806 69
1777557811 69
1777557816 69
1777557821 69
1777557826 69
```
</details>

---

