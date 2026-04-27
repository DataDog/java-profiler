---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-26 21:26:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 11 |
| Allocations | 397 |

<details>
<summary>CPU Timeline (2 unique values: 71-96 cores)</summary>

```
1777252663 71
1777252668 71
1777252673 71
1777252678 71
1777252683 71
1777252688 71
1777252693 71
1777252698 71
1777252703 71
1777252708 71
1777252713 71
1777252718 71
1777252723 71
1777252728 71
1777252733 71
1777252738 71
1777252743 71
1777252748 71
1777252753 71
1777252758 96
```
</details>

---

