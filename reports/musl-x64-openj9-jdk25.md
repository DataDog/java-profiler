---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:43:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 68-78 cores)</summary>

```
1793187551 68
1793187556 68
1793187561 68
1793187566 68
1793187571 68
1793187576 68
1793187581 68
1793187586 68
1793187591 68
1793187596 68
1793187601 70
1793187606 70
1793187611 70
1793187616 70
1793187622 70
1793187627 70
1793187632 70
1793187637 70
1793187642 78
1793187647 78
```
</details>

---

