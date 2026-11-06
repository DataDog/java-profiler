---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 05:58:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 11 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793962453 36
1793962458 36
1793962463 36
1793962468 36
1793962473 36
1793962478 36
1793962483 36
1793962488 36
1793962493 36
1793962498 36
1793962503 36
1793962508 36
1793962513 36
1793962518 36
1793962523 36
1793962528 36
1793962533 36
1793962538 36
1793962543 36
1793962548 36
```
</details>

---

