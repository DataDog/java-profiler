---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-03 04:34:56 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1791016258 38
1791016263 38
1791016268 38
1791016273 38
1791016278 38
1791016283 38
1791016288 43
1791016293 43
1791016298 43
1791016303 43
1791016308 43
1791016313 43
1791016318 43
1791016323 43
1791016328 43
1791016333 43
1791016338 43
1791016343 43
1791016348 43
1791016353 43
```
</details>

---

