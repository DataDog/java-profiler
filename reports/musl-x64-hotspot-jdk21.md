---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:47:16 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1794408144 49
1794408149 49
1794408154 49
1794408159 49
1794408164 49
1794408169 49
1794408174 49
1794408179 44
1794408184 44
1794408189 44
1794408194 44
1794408199 44
1794408204 44
1794408209 44
1794408214 44
1794408219 44
1794408224 44
1794408229 44
1794408234 44
1794408239 44
```
</details>

---

