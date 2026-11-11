---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:16 EST

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
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 87-89 cores)</summary>

```
1794408134 89
1794408139 89
1794408144 87
1794408149 87
1794408154 87
1794408159 87
1794408164 87
1794408169 87
1794408174 87
1794408179 87
1794408184 87
1794408189 87
1794408194 87
1794408199 87
1794408204 87
1794408209 87
1794408214 87
1794408219 87
1794408224 87
1794408229 87
```
</details>

---

