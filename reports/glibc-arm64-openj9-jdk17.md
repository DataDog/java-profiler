---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:31:16 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 11 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1795008253 29
1795008258 29
1795008263 29
1795008268 29
1795008273 29
1795008278 29
1795008283 29
1795008288 29
1795008293 29
1795008298 34
1795008303 34
1795008308 34
1795008313 34
1795008318 34
1795008323 34
1795008328 34
1795008333 34
1795008338 22
1795008343 22
1795008348 22
```
</details>

---

