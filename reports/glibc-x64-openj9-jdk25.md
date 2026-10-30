---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 08:17:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793362401 30
1793362406 30
1793362411 30
1793362416 30
1793362421 30
1793362426 32
1793362431 32
1793362436 28
1793362441 28
1793362446 28
1793362451 28
1793362456 28
1793362461 28
1793362466 28
1793362471 28
1793362476 30
1793362481 30
1793362486 30
1793362491 30
1793362496 30
```
</details>

---

