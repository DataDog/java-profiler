---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:47:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (6 unique values: 40-48 cores)</summary>

```
1794480184 40
1794480189 40
1794480194 40
1794480199 44
1794480204 44
1794480209 43
1794480214 43
1794480219 47
1794480224 47
1794480229 48
1794480234 48
1794480239 48
1794480244 48
1794480249 48
1794480254 48
1794480259 48
1794480264 46
1794480269 46
1794480274 46
1794480279 46
```
</details>

---

