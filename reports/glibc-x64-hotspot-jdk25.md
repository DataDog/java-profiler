---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 52-56 cores)</summary>

```
1795429092 56
1795429097 56
1795429102 56
1795429107 56
1795429112 56
1795429117 56
1795429122 56
1795429127 56
1795429132 56
1795429137 56
1795429142 56
1795429147 56
1795429152 56
1795429157 56
1795429162 56
1795429167 56
1795429172 56
1795429177 56
1795429182 56
1795429187 54
```
</details>

---

