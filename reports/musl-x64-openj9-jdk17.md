---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-06 09:39:29 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 10 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 53-57 cores)</summary>

```
1770388400 53
1770388405 53
1770388410 57
1770388415 57
1770388420 57
1770388425 57
1770388430 57
1770388435 57
1770388440 57
1770388445 57
1770388450 57
1770388455 57
1770388460 57
1770388465 57
1770388470 57
1770388475 57
1770388481 57
1770388486 57
1770388491 57
1770388496 57
```
</details>

---

