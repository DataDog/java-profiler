---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:01:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 74-86 cores)</summary>

```
1794567349 86
1794567354 86
1794567359 86
1794567364 86
1794567369 86
1794567374 86
1794567379 86
1794567384 86
1794567389 86
1794567394 86
1794567399 86
1794567404 86
1794567409 86
1794567414 86
1794567419 86
1794567424 86
1794567429 86
1794567434 74
1794567439 74
1794567444 74
```
</details>

---

