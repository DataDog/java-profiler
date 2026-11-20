---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 08:32:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1795181292 63
1795181297 63
1795181302 63
1795181307 63
1795181312 63
1795181317 63
1795181322 61
1795181327 61
1795181332 61
1795181337 61
1795181342 61
1795181347 61
1795181352 61
1795181357 61
1795181362 61
1795181367 61
1795181372 61
1795181377 61
1795181382 61
1795181387 61
```
</details>

---

