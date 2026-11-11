---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 20:36:46 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 34-43 cores)</summary>

```
1794360783 43
1794360788 43
1794360793 43
1794360798 43
1794360803 43
1794360808 43
1794360813 43
1794360818 43
1794360823 43
1794360828 43
1794360833 43
1794360838 43
1794360843 43
1794360848 43
1794360853 43
1794360858 43
1794360863 43
1794360868 39
1794360873 39
1794360878 34
```
</details>

---

