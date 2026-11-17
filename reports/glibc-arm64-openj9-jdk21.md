---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 00:08:20 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
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
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794891850 34
1794891855 34
1794891860 34
1794891865 34
1794891870 34
1794891875 34
1794891880 34
1794891885 34
1794891890 39
1794891895 39
1794891900 39
1794891905 39
1794891910 39
1794891915 39
1794891920 39
1794891925 39
1794891930 34
1794891935 34
1794891940 34
1794891945 34
```
</details>

---

