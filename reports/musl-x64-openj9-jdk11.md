---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (3 unique values: 39-59 cores)</summary>

```
1795434730 39
1795434735 39
1795434740 59
1795434745 59
1795434750 59
1795434755 59
1795434760 59
1795434765 59
1795434770 57
1795434775 57
1795434780 57
1795434785 57
1795434790 57
1795434795 57
1795434800 57
1795434805 57
1795434810 57
1795434815 57
1795434820 57
1795434825 57
```
</details>

---

