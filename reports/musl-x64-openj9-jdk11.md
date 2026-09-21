---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-20 21:20:07 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 18-32 cores)</summary>

```
1789953257 18
1789953262 18
1789953267 18
1789953272 18
1789953277 18
1789953282 18
1789953287 18
1789953292 18
1789953297 18
1789953302 32
1789953307 32
1789953312 32
1789953317 32
1789953322 32
1789953327 32
1789953332 32
1789953337 32
1789953342 32
1789953347 32
1789953352 32
```
</details>

---

