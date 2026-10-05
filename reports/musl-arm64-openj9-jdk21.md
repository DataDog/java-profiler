---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1791193594 48
1791193599 48
1791193604 48
1791193609 48
1791193614 48
1791193619 48
1791193624 48
1791193629 48
1791193634 48
1791193639 48
1791193644 48
1791193649 48
1791193654 48
1791193659 48
1791193664 48
1791193669 48
1791193674 48
1791193679 48
1791193684 48
1791193689 48
```
</details>

---

