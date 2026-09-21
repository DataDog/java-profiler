---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 52-62 cores)</summary>

```
1789995378 62
1789995383 62
1789995388 52
1789995393 52
1789995398 52
1789995403 52
1789995408 52
1789995413 52
1789995418 52
1789995423 52
1789995428 52
1789995433 52
1789995438 52
1789995443 52
1789995448 52
1789995453 52
1789995458 52
1789995463 52
1789995468 52
1789995473 52
```
</details>

---

