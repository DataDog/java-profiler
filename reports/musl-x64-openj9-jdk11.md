---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:34:31 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794587391 94
1794587396 94
1794587401 94
1794587406 94
1794587411 94
1794587416 94
1794587421 94
1794587426 94
1794587431 94
1794587436 92
1794587441 92
1794587446 92
1794587451 92
1794587456 92
1794587461 92
1794587466 92
1794587471 92
1794587476 92
1794587481 92
1794587486 92
```
</details>

---

