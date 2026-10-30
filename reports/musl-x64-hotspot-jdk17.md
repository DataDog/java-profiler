---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:23:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 307 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793373493 30
1793373498 30
1793373503 30
1793373508 30
1793373513 30
1793373518 30
1793373523 30
1793373528 30
1793373533 30
1793373538 30
1793373543 30
1793373548 30
1793373553 32
1793373558 32
1793373563 32
1793373568 32
1793373573 30
1793373579 30
1793373584 30
1793373589 30
```
</details>

---

