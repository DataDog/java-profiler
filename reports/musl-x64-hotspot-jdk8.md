---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 05:26:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 63-70 cores)</summary>

```
1789982407 65
1789982412 65
1789982417 65
1789982422 65
1789982427 65
1789982432 65
1789982437 65
1789982442 65
1789982447 65
1789982452 65
1789982457 65
1789982462 65
1789982467 65
1789982472 65
1789982477 63
1789982482 63
1789982487 63
1789982492 63
1789982497 63
1789982502 63
```
</details>

---

