---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 10 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (6 unique values: 67-85 cores)</summary>

```
1778158401 85
1778158406 85
1778158411 85
1778158416 81
1778158421 81
1778158426 81
1778158431 74
1778158436 74
1778158441 74
1778158446 71
1778158451 71
1778158456 71
1778158461 71
1778158466 71
1778158471 71
1778158476 71
1778158481 71
1778158486 67
1778158491 67
1778158496 67
```
</details>

---

