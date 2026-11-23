---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 00:00:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 14 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795409804 34
1795409809 34
1795409814 34
1795409819 34
1795409824 34
1795409829 34
1795409834 34
1795409839 29
1795409844 29
1795409849 29
1795409854 29
1795409859 29
1795409864 29
1795409869 29
1795409874 29
1795409879 34
1795409884 34
1795409889 34
1795409894 34
1795409899 34
```
</details>

---

