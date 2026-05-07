---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:44:41 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 36-46 cores)</summary>

```
1778175586 36
1778175591 36
1778175596 41
1778175601 41
1778175606 41
1778175611 41
1778175616 41
1778175621 46
1778175626 46
1778175631 46
1778175636 46
1778175641 46
1778175646 46
1778175651 46
1778175656 46
1778175661 46
1778175666 46
1778175671 46
1778175676 46
1778175681 46
```
</details>

---

