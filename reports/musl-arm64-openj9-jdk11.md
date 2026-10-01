---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:20:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1007 |
| Sample Rate | 16.78/sec |
| Health Score | 1049% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1790853344 41
1790853349 52
1790853354 52
1790853359 52
1790853364 52
1790853369 52
1790853374 52
1790853379 52
1790853384 52
1790853389 52
1790853394 52
1790853399 52
1790853404 52
1790853409 52
1790853414 52
1790853419 52
1790853424 52
1790853429 52
1790853434 52
1790853439 52
```
</details>

---

