---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:33:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 35-79 cores)</summary>

```
1789716396 35
1789716401 35
1789716406 35
1789716411 35
1789716416 35
1789716421 35
1789716426 35
1789716431 35
1789716436 35
1789716442 35
1789716447 35
1789716452 43
1789716457 43
1789716462 43
1789716467 43
1789716472 43
1789716477 43
1789716482 43
1789716487 43
1789716492 79
```
</details>

---

