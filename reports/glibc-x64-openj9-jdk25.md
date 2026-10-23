---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 12:24:20 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 78-91 cores)</summary>

```
1792772471 78
1792772476 78
1792772481 78
1792772486 78
1792772491 78
1792772496 89
1792772501 89
1792772506 89
1792772511 89
1792772516 89
1792772521 89
1792772526 89
1792772531 89
1792772536 89
1792772541 89
1792772546 89
1792772551 89
1792772556 89
1792772561 89
1792772566 89
```
</details>

---

