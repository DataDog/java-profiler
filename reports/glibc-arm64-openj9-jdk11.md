---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 08:04:09 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791806339 48
1791806344 48
1791806349 48
1791806354 48
1791806359 43
1791806364 43
1791806369 43
1791806374 43
1791806379 38
1791806384 38
1791806389 38
1791806394 38
1791806399 38
1791806404 38
1791806409 38
1791806414 38
1791806419 43
1791806424 43
1791806429 43
1791806434 43
```
</details>

---

