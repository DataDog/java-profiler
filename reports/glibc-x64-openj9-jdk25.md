---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 07:26:49 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1792408971 92
1792408976 92
1792408981 96
1792408986 96
1792408991 96
1792408996 96
1792409001 96
1792409006 96
1792409011 96
1792409016 96
1792409021 96
1792409026 96
1792409031 96
1792409036 96
1792409041 96
1792409046 96
1792409051 96
1792409056 96
1792409061 96
1792409066 96
```
</details>

---

