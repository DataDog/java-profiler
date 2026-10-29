---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 16:31:12 EDT

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
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 35-38 cores)</summary>

```
1793305602 36
1793305607 36
1793305612 38
1793305617 38
1793305622 38
1793305627 38
1793305632 38
1793305638 38
1793305643 38
1793305648 38
1793305653 38
1793305658 38
1793305663 38
1793305668 38
1793305673 38
1793305678 35
1793305683 35
1793305688 35
1793305693 35
1793305698 35
```
</details>

---

