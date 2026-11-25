---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:19:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1795641301 96
1795641306 96
1795641311 96
1795641316 96
1795641321 96
1795641326 96
1795641331 96
1795641336 94
1795641341 94
1795641346 94
1795641351 94
1795641356 94
1795641361 94
1795641366 94
1795641371 94
1795641376 94
1795641381 94
1795641386 94
1795641391 94
1795641396 94
```
</details>

---

