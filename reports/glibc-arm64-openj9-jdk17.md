---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:12:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 52-64 cores)</summary>

```
1795097278 52
1795097283 52
1795097288 52
1795097293 52
1795097298 52
1795097303 52
1795097308 52
1795097313 52
1795097318 52
1795097323 52
1795097328 52
1795097333 52
1795097338 52
1795097343 52
1795097348 52
1795097353 52
1795097358 52
1795097363 52
1795097368 52
1795097373 57
```
</details>

---

