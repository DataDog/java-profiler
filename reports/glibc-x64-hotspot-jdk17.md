---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:16:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 77-82 cores)</summary>

```
1795691222 77
1795691227 77
1795691232 77
1795691237 77
1795691243 77
1795691248 77
1795691253 77
1795691258 77
1795691263 77
1795691268 77
1795691273 77
1795691278 77
1795691283 82
1795691288 82
1795691293 82
1795691298 82
1795691303 82
1795691308 80
1795691313 80
1795691318 80
```
</details>

---

