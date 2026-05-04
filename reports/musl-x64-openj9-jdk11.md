---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:22:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1069 |
| Sample Rate | 17.82/sec |
| Health Score | 1114% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1777857401 57
1777857406 60
1777857411 60
1777857416 60
1777857421 60
1777857426 60
1777857431 60
1777857436 60
1777857441 60
1777857446 60
1777857451 60
1777857456 60
1777857461 60
1777857466 60
1777857471 60
1777857476 60
1777857481 60
1777857486 60
1777857491 56
1777857496 56
```
</details>

---

