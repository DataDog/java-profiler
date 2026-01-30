---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-30 05:41:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1259 |
| Sample Rate | 20.98/sec |
| Health Score | 1311% |
| Threads | 12 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1769769336 38
1769769341 38
1769769346 38
1769769351 38
1769769356 38
1769769361 38
1769769366 38
1769769371 36
1769769376 36
1769769381 36
1769769386 36
1769769391 36
1769769396 36
1769769401 36
1769769406 36
1769769411 36
1769769416 36
1769769421 36
1769769426 36
1769769431 38
```
</details>

---

