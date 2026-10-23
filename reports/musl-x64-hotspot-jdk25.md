---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 12:24:21 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 50-55 cores)</summary>

```
1792772437 50
1792772442 50
1792772447 50
1792772452 53
1792772457 53
1792772462 53
1792772467 53
1792772472 53
1792772477 53
1792772482 53
1792772487 53
1792772492 53
1792772497 53
1792772502 53
1792772507 53
1792772512 53
1792772517 53
1792772522 53
1792772527 53
1792772532 53
```
</details>

---

