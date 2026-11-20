---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 08:32:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 30-64 cores)</summary>

```
1795181327 30
1795181332 30
1795181337 30
1795181342 30
1795181347 30
1795181352 30
1795181357 30
1795181362 30
1795181367 30
1795181372 50
1795181377 50
1795181382 50
1795181387 50
1795181392 50
1795181397 50
1795181402 50
1795181407 50
1795181412 50
1795181417 50
1795181422 50
```
</details>

---

