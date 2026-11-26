---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:16:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 10 |
| Allocations | 158 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795691263 44
1795691268 44
1795691273 44
1795691278 44
1795691283 44
1795691288 64
1795691293 64
1795691298 64
1795691303 64
1795691308 64
1795691313 64
1795691318 64
1795691323 64
1795691328 64
1795691333 64
1795691338 64
1795691343 64
1795691348 64
1795691353 64
1795691358 64
```
</details>

---

