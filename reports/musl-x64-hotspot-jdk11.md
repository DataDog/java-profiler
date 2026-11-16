---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 06:58:39 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (4 unique values: 66-71 cores)</summary>

```
1794830063 67
1794830068 67
1794830073 67
1794830078 67
1794830084 67
1794830089 67
1794830094 67
1794830099 67
1794830104 69
1794830109 69
1794830114 69
1794830119 69
1794830124 71
1794830129 71
1794830134 71
1794830139 71
1794830144 71
1794830149 71
1794830154 71
1794830159 71
```
</details>

---

