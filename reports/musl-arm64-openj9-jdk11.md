---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 10:29:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 37-42 cores)</summary>

```
1793197453 42
1793197458 42
1793197463 42
1793197468 42
1793197473 42
1793197478 42
1793197483 41
1793197488 41
1793197493 41
1793197498 41
1793197503 41
1793197508 42
1793197513 42
1793197518 42
1793197523 42
1793197528 42
1793197533 42
1793197538 42
1793197543 42
1793197548 42
```
</details>

---

