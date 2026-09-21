---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789982382 48
1789982387 48
1789982392 48
1789982397 48
1789982402 48
1789982407 48
1789982412 48
1789982417 48
1789982422 48
1789982427 48
1789982432 48
1789982437 48
1789982442 48
1789982447 48
1789982452 48
1789982457 48
1789982462 48
1789982467 48
1789982472 48
1789982477 48
```
</details>

---

