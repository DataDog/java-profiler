---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 05:30:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 36-50 cores)</summary>

```
1777541133 36
1777541138 36
1777541143 36
1777541148 36
1777541153 36
1777541158 36
1777541163 36
1777541168 45
1777541173 45
1777541178 45
1777541183 45
1777541188 45
1777541193 45
1777541198 45
1777541203 45
1777541208 45
1777541213 45
1777541218 45
1777541223 45
1777541228 45
```
</details>

---

