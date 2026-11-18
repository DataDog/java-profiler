---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:03:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (6 unique values: 43-69 cores)</summary>

```
1795013875 43
1795013880 43
1795013885 60
1795013890 60
1795013895 61
1795013900 61
1795013905 61
1795013910 61
1795013915 61
1795013920 61
1795013925 61
1795013930 66
1795013935 66
1795013940 69
1795013945 69
1795013950 69
1795013955 69
1795013960 69
1795013965 69
1795013970 69
```
</details>

---

