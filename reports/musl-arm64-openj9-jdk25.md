---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 10:29:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793978584 48
1793978589 48
1793978594 48
1793978599 48
1793978604 48
1793978609 48
1793978614 48
1793978619 48
1793978624 48
1793978629 48
1793978634 48
1793978639 48
1793978645 48
1793978650 48
1793978655 48
1793978660 48
1793978665 48
1793978670 48
1793978675 48
1793978680 48
```
</details>

---

