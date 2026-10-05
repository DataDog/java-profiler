---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 06:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 10-16 cores)</summary>

```
1791196568 10
1791196573 10
1791196578 10
1791196583 10
1791196588 10
1791196593 10
1791196598 10
1791196603 16
1791196608 16
1791196613 12
1791196618 12
1791196623 12
1791196628 12
1791196633 12
1791196638 12
1791196643 12
1791196648 12
1791196653 12
1791196658 12
1791196663 12
```
</details>

---

