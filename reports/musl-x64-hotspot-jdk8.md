---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-07 17:34:40 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 56-65 cores)</summary>

```
1778189463 61
1778189468 61
1778189473 61
1778189478 63
1778189483 63
1778189488 65
1778189493 65
1778189498 65
1778189503 65
1778189508 65
1778189513 60
1778189518 60
1778189523 60
1778189528 60
1778189533 56
1778189538 56
1778189543 56
1778189548 58
1778189553 58
1778189558 60
```
</details>

---

