---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:02:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789995363 48
1789995368 48
1789995373 48
1789995378 48
1789995383 48
1789995388 48
1789995393 48
1789995398 48
1789995403 48
1789995408 48
1789995413 48
1789995418 48
1789995423 48
1789995428 48
1789995433 46
1789995438 46
1789995443 46
1789995448 46
1789995453 46
1789995458 46
```
</details>

---

