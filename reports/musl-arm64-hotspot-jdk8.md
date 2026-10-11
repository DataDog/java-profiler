---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-11 11:15:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1791731346 28
1791731351 28
1791731356 28
1791731361 28
1791731366 28
1791731371 28
1791731376 28
1791731381 28
1791731386 28
1791731391 28
1791731396 28
1791731401 28
1791731406 28
1791731411 48
1791731416 48
1791731421 48
1791731427 48
1791731432 48
1791731437 48
1791731442 48
```
</details>

---

