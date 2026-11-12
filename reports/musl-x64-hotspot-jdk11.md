---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:53:42 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794491325 92
1794491330 92
1794491335 94
1794491340 94
1794491345 94
1794491350 94
1794491355 94
1794491360 94
1794491365 94
1794491370 94
1794491375 94
1794491381 94
1794491386 94
1794491391 94
1794491396 94
1794491401 94
1794491406 94
1794491411 94
1794491416 94
1794491421 94
```
</details>

---

