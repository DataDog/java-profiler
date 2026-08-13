---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 11:55:09 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 12 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1786636197 51
1786636202 51
1786636207 51
1786636212 49
1786636217 49
1786636222 49
1786636227 49
1786636232 49
1786636237 49
1786636242 51
1786636247 51
1786636252 51
1786636257 51
1786636262 51
1786636267 51
1786636272 51
1786636277 51
1786636282 51
1786636287 51
1786636292 51
```
</details>

---

