---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 16:33:59 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1777321755 43
1777321760 43
1777321765 43
1777321770 43
1777321775 43
1777321780 43
1777321785 46
1777321790 46
1777321795 46
1777321800 46
1777321805 46
1777321810 46
1777321815 46
1777321820 46
1777321825 46
1777321830 41
1777321835 41
1777321840 41
1777321845 41
1777321850 41
```
</details>

---

