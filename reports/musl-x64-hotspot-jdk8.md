---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 73-76 cores)</summary>

```
1794001097 73
1794001102 75
1794001107 75
1794001112 75
1794001117 74
1794001122 74
1794001127 74
1794001132 76
1794001137 76
1794001142 74
1794001147 74
1794001152 74
1794001157 74
1794001162 74
1794001167 74
1794001172 74
1794001177 74
1794001182 74
1794001187 76
1794001192 76
```
</details>

---

