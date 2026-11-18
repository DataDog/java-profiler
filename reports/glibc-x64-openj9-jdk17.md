---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:48:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 12 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 58-61 cores)</summary>

```
1795027344 58
1795027349 58
1795027354 58
1795027359 60
1795027364 60
1795027369 60
1795027374 60
1795027379 60
1795027384 61
1795027389 61
1795027394 61
1795027399 61
1795027404 61
1795027409 61
1795027414 61
1795027419 61
1795027424 61
1795027429 61
1795027434 61
1795027439 61
```
</details>

---

