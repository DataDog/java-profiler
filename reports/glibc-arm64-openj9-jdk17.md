---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:57:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794498772 34
1794498778 34
1794498783 34
1794498788 34
1794498793 34
1794498798 34
1794498803 34
1794498808 34
1794498813 39
1794498818 39
1794498823 34
1794498828 34
1794498833 34
1794498838 34
1794498843 34
1794498848 34
1794498853 34
1794498858 34
1794498863 34
1794498868 34
```
</details>

---

