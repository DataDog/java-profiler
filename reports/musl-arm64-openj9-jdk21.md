---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
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
1795641391 47
1795641396 47
1795641401 47
1795641406 47
1795641411 47
1795641416 47
1795641421 64
```
</details>

---

