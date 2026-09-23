---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:27:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790173288 50
1790173293 50
1790173298 50
1790173303 50
1790173308 50
1790173313 50
1790173318 50
1790173323 50
1790173328 50
1790173333 50
1790173338 50
1790173343 50
1790173348 50
1790173353 50
1790173358 50
1790173363 50
1790173368 50
1790173373 50
1790173378 50
1790173383 50
```
</details>

---

