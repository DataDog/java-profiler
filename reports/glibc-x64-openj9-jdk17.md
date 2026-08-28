---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-28 08:40:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1787920571 54
1787920576 54
1787920581 54
1787920586 54
1787920591 52
1787920596 52
1787920601 52
1787920606 50
1787920611 50
1787920616 48
1787920621 48
1787920626 48
1787920631 50
1787920636 50
1787920641 50
1787920646 50
1787920651 52
1787920656 52
1787920661 52
1787920666 52
```
</details>

---

