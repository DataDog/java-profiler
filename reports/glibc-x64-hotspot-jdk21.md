---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:46:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 22-30 cores)</summary>

```
1794408094 30
1794408099 30
1794408104 30
1794408109 30
1794408114 30
1794408119 30
1794408124 30
1794408129 30
1794408134 30
1794408139 30
1794408144 30
1794408149 30
1794408154 30
1794408159 24
1794408164 24
1794408169 24
1794408174 24
1794408179 24
1794408184 24
1794408189 24
```
</details>

---

