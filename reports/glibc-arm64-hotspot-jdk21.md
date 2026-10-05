---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:52:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 10 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791193639 43
1791193644 43
1791193649 43
1791193654 43
1791193659 43
1791193664 43
1791193669 43
1791193674 43
1791193679 43
1791193684 43
1791193689 48
1791193694 48
1791193699 48
1791193704 48
1791193709 48
1791193714 48
1791193719 48
1791193724 48
1791193729 48
1791193734 48
```
</details>

---

