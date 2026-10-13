---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-13 01:03:54 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1791867576 75
1791867581 75
1791867586 75
1791867591 75
1791867596 77
1791867601 77
1791867606 77
1791867611 77
1791867616 77
1791867621 77
1791867626 77
1791867631 79
1791867636 79
1791867641 79
1791867646 79
1791867651 79
1791867656 79
1791867661 79
1791867666 79
1791867672 79
```
</details>

---

