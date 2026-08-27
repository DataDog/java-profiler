---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-27 09:40:17 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787837718 66
1787837723 64
1787837728 64
1787837733 64
1787837738 64
1787837743 64
1787837748 64
1787837753 64
1787837758 64
1787837763 64
1787837768 64
1787837773 64
1787837778 64
1787837783 66
1787837788 66
1787837793 66
1787837798 66
1787837803 66
1787837808 66
1787837813 66
```
</details>

---

