---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 05:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1786095976 32
1786095981 32
1786095986 28
1786095991 28
1786095996 28
1786096001 28
1786096006 28
1786096011 28
1786096016 28
1786096021 28
1786096026 28
1786096031 28
1786096036 28
1786096041 28
1786096046 28
1786096051 28
1786096056 28
1786096061 28
1786096066 28
1786096071 28
```
</details>

---

