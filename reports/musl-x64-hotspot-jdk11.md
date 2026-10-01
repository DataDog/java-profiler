---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 09:06:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 43-61 cores)</summary>

```
1790859714 61
1790859719 61
1790859724 61
1790859729 61
1790859734 59
1790859739 59
1790859744 59
1790859749 61
1790859754 61
1790859759 61
1790859764 61
1790859769 61
1790859774 61
1790859779 61
1790859784 61
1790859789 51
1790859794 51
1790859799 51
1790859804 51
1790859809 51
```
</details>

---

