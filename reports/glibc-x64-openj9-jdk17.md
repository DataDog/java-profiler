---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:54:15 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1789667267 22
1789667272 22
1789667277 24
1789667282 24
1789667287 24
1789667292 24
1789667297 24
1789667302 24
1789667307 22
1789667312 22
1789667317 22
1789667322 22
1789667327 22
1789667332 22
1789667337 22
1789667342 22
1789667347 22
1789667352 22
1789667357 22
1789667362 22
```
</details>

---

