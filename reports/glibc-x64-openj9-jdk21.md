---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:54:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 30-31 cores)</summary>

```
1789667281 30
1789667287 30
1789667292 30
1789667297 31
1789667302 31
1789667307 31
1789667312 31
1789667317 31
1789667322 31
1789667327 31
1789667332 31
1789667337 31
1789667342 31
1789667347 31
1789667352 31
1789667357 31
1789667362 31
1789667367 31
1789667372 31
1789667377 31
```
</details>

---

