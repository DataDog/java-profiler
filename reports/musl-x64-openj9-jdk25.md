---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 10:07:44 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 12 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1773237472 23
1773237477 23
1773237482 23
1773237487 23
1773237492 23
1773237497 23
1773237502 23
1773237507 23
1773237512 23
1773237517 23
1773237522 32
1773237527 32
1773237532 32
1773237537 32
1773237542 32
1773237547 32
1773237552 32
1773237557 32
1773237562 32
1773237567 32
```
</details>

---

