---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 05:50:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1786095996 21
1786096001 21
1786096006 21
1786096011 21
1786096016 21
1786096021 21
1786096026 21
1786096031 21
1786096036 21
1786096041 21
1786096046 21
1786096051 32
1786096056 32
1786096061 32
1786096066 32
1786096071 29
1786096076 29
1786096081 29
1786096086 29
1786096091 29
```
</details>

---

