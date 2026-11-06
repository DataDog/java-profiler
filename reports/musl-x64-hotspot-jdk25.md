---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 05:58:31 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 55-61 cores)</summary>

```
1793962423 55
1793962428 55
1793962433 61
1793962438 61
1793962443 61
1793962448 61
1793962453 61
1793962458 61
1793962463 61
1793962468 61
1793962473 61
1793962478 61
1793962483 61
1793962488 61
1793962493 61
1793962498 61
1793962503 61
1793962508 61
1793962513 61
1793962518 61
```
</details>

---

