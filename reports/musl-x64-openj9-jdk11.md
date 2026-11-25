---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:22:56 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 4 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 68-96 cores)</summary>

```
1795641366 68
1795641371 68
1795641376 96
1795641381 96
1795641386 96
1795641391 96
1795641396 68
1795641401 68
1795641406 68
1795641411 68
1795641416 68
1795641421 68
1795641426 68
1795641431 68
1795641436 68
1795641441 68
1795641446 68
1795641451 68
1795641456 68
1795641461 68
```
</details>

---

