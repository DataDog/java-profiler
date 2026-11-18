---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 14:19:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1795029339 35
1795029344 35
1795029349 35
1795029354 35
1795029359 35
1795029364 35
1795029369 35
1795029374 35
1795029379 35
1795029384 35
1795029389 35
1795029394 30
1795029399 30
1795029404 30
1795029409 30
1795029414 30
1795029419 30
1795029424 30
1795029429 30
1795029434 30
```
</details>

---

