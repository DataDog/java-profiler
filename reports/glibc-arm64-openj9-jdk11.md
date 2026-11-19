---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:13:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 40-50 cores)</summary>

```
1795097243 40
1795097248 40
1795097253 40
1795097258 40
1795097263 40
1795097268 40
1795097273 40
1795097278 40
1795097283 45
1795097288 45
1795097293 45
1795097298 50
1795097303 50
1795097308 50
1795097313 50
1795097318 50
1795097323 50
1795097328 50
1795097333 50
1795097338 50
```
</details>

---

