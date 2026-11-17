---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:37:07 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794936747 89
1794936752 89
1794936757 89
1794936762 89
1794936767 89
1794936772 89
1794936777 89
1794936782 89
1794936787 91
1794936792 91
1794936797 93
1794936802 93
1794936807 93
1794936813 93
1794936818 93
1794936823 93
1794936828 93
1794936833 93
1794936838 93
1794936843 93
```
</details>

---

