---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 01:05:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 89-94 cores)</summary>

```
1793163671 89
1793163676 89
1793163681 89
1793163686 89
1793163691 89
1793163696 89
1793163701 89
1793163706 89
1793163711 94
1793163716 94
1793163721 94
1793163726 94
1793163731 94
1793163736 94
1793163741 94
1793163746 94
1793163751 94
1793163756 94
1793163761 94
1793163766 94
```
</details>

---

