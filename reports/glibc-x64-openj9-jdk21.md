---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:26:05 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 29-34 cores)</summary>

```
1773393638 32
1773393643 32
1773393648 32
1773393653 32
1773393658 32
1773393663 32
1773393668 32
1773393673 32
1773393678 32
1773393683 34
1773393688 34
1773393693 34
1773393698 34
1773393703 29
1773393708 29
1773393713 31
1773393718 31
1773393723 31
1773393728 31
1773393733 31
```
</details>

---

