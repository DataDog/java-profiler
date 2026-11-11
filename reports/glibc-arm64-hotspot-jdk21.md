---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 08:05:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (5 unique values: 37-42 cores)</summary>

```
1794402096 41
1794402101 41
1794402106 40
1794402111 40
1794402116 40
1794402121 40
1794402126 42
1794402131 42
1794402136 42
1794402141 42
1794402146 42
1794402151 42
1794402156 42
1794402161 42
1794402166 42
1794402171 37
1794402176 37
1794402181 37
1794402186 37
1794402191 39
```
</details>

---

