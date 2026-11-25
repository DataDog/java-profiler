---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:19:52 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 47-75 cores)</summary>

```
1795641311 47
1795641316 47
1795641321 47
1795641326 47
1795641331 47
1795641336 47
1795641341 47
1795641346 47
1795641351 47
1795641356 47
1795641361 47
1795641366 47
1795641371 47
1795641376 47
1795641381 47
1795641386 47
1795641392 47
1795641397 49
1795641402 49
1795641407 75
```
</details>

---

