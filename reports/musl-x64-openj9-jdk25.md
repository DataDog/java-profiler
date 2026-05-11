---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 11:23:15 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 84-91 cores)</summary>

```
1778512692 91
1778512697 91
1778512702 91
1778512707 89
1778512712 89
1778512717 84
1778512722 84
1778512727 84
1778512732 84
1778512737 84
1778512742 84
1778512747 84
1778512752 84
1778512757 84
1778512762 84
1778512767 84
1778512772 86
1778512777 86
1778512782 86
1778512787 86
```
</details>

---

