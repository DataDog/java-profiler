---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:21:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 31-43 cores)</summary>

```
1794323845 36
1794323850 36
1794323855 36
1794323860 36
1794323865 36
1794323870 36
1794323875 31
1794323880 31
1794323885 31
1794323890 31
1794323895 31
1794323900 31
1794323905 31
1794323910 31
1794323915 31
1794323920 31
1794323925 31
1794323930 31
1794323935 31
1794323940 31
```
</details>

---

