---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 42-62 cores)</summary>

```
1791193613 42
1791193618 42
1791193623 42
1791193628 42
1791193633 42
1791193638 42
1791193643 42
1791193648 42
1791193653 42
1791193658 42
1791193663 42
1791193668 42
1791193673 42
1791193678 42
1791193683 42
1791193688 62
1791193693 62
1791193698 62
1791193703 62
1791193708 62
```
</details>

---

