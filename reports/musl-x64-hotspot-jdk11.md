---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:25:51 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (5 unique values: 85-90 cores)</summary>

```
1794583279 85
1794583284 85
1794583289 87
1794583294 87
1794583299 87
1794583304 87
1794583309 87
1794583314 90
1794583319 90
1794583324 90
1794583329 90
1794583334 90
1794583339 90
1794583344 90
1794583349 90
1794583354 90
1794583359 90
1794583364 90
1794583369 90
1794583374 88
```
</details>

---

