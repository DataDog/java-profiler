---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:16:16 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 84-89 cores)</summary>

```
1795691248 89
1795691253 89
1795691258 89
1795691263 89
1795691268 89
1795691273 89
1795691278 89
1795691283 85
1795691288 85
1795691293 85
1795691298 85
1795691303 85
1795691308 85
1795691313 85
1795691318 85
1795691323 85
1795691328 85
1795691333 84
1795691338 84
1795691343 84
```
</details>

---

