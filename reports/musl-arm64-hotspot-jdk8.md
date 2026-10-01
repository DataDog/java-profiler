---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-01 09:06:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 32-48 cores)</summary>

```
1790859719 37
1790859724 37
1790859729 37
1790859734 37
1790859739 37
1790859744 37
1790859749 37
1790859754 37
1790859759 37
1790859764 32
1790859769 32
1790859774 32
1790859779 32
1790859784 41
1790859789 41
1790859794 41
1790859799 41
1790859804 46
1790859809 46
1790859814 46
```
</details>

---

