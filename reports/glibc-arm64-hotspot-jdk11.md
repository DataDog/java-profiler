---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:09:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790168624 43
1790168629 43
1790168634 43
1790168639 43
1790168644 43
1790168649 43
1790168654 43
1790168659 48
1790168664 48
1790168669 48
1790168674 48
1790168679 48
1790168684 48
1790168689 48
1790168694 48
1790168699 48
1790168704 48
1790168709 48
1790168714 48
1790168719 48
```
</details>

---

