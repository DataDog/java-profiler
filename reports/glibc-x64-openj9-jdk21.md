---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 00:00:37 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 34-55 cores)</summary>

```
1795409769 55
1795409774 55
1795409779 55
1795409784 55
1795409789 36
1795409794 36
1795409799 36
1795409804 36
1795409809 36
1795409814 36
1795409819 36
1795409824 36
1795409829 38
1795409834 38
1795409839 34
1795409844 34
1795409849 34
1795409854 34
1795409859 34
1795409864 34
```
</details>

---

