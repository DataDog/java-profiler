---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 05:45:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 57-79 cores)</summary>

```
1786527677 65
1786527682 57
1786527687 57
1786527692 57
1786527697 57
1786527702 57
1786527707 57
1786527712 79
1786527717 79
1786527722 77
1786527727 77
1786527732 77
1786527737 77
1786527742 77
1786527747 77
1786527752 77
1786527757 77
1786527762 77
1786527767 77
1786527772 77
```
</details>

---

