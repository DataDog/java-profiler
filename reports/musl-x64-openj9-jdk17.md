---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 01:03:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1791867551 15
1791867556 15
1791867561 15
1791867566 15
1791867571 15
1791867576 15
1791867581 15
1791867586 17
1791867591 17
1791867596 17
1791867601 17
1791867606 17
1791867611 17
1791867616 17
1791867621 17
1791867626 17
1791867631 17
1791867636 17
1791867641 17
1791867646 17
```
</details>

---

