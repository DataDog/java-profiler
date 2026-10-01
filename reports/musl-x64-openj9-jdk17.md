---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 08:26:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 9 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 18-27 cores)</summary>

```
1790857312 18
1790857317 18
1790857322 18
1790857327 18
1790857332 18
1790857337 18
1790857342 18
1790857347 18
1790857352 18
1790857357 18
1790857362 18
1790857367 18
1790857372 18
1790857377 18
1790857382 18
1790857387 18
1790857392 27
1790857397 27
1790857402 27
1790857407 27
```
</details>

---

