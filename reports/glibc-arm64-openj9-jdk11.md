---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:19:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795641311 44
1795641316 44
1795641321 44
1795641326 44
1795641331 44
1795641336 44
1795641341 64
1795641346 64
1795641351 64
1795641356 64
1795641361 64
1795641366 64
1795641371 47
1795641376 47
1795641381 47
1795641386 47
1795641391 47
1795641396 47
1795641401 47
1795641406 47
```
</details>

---

