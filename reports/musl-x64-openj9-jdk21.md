---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 13:49:23 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1792777503 30
1792777508 30
1792777513 30
1792777518 30
1792777523 30
1792777528 30
1792777533 30
1792777538 28
1792777543 28
1792777548 28
1792777553 28
1792777558 28
1792777563 28
1792777568 28
1792777573 30
1792777578 30
1792777583 32
1792777588 32
1792777593 32
1792777598 32
```
</details>

---

