---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:21:06 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 45-64 cores)</summary>

```
1777857366 45
1777857371 45
1777857376 45
1777857381 45
1777857386 45
1777857391 45
1777857396 45
1777857401 45
1777857406 45
1777857411 64
1777857416 64
1777857421 64
1777857426 64
1777857431 64
1777857436 64
1777857441 64
1777857446 64
1777857451 64
1777857456 64
1777857461 64
```
</details>

---

