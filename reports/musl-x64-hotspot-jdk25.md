---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 07:23:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1787224728 64
1787224733 56
1787224738 56
1787224743 56
1787224748 56
1787224753 56
1787224758 56
1787224763 56
1787224768 56
1787224773 56
1787224778 56
1787224783 56
1787224788 56
1787224793 56
1787224798 56
1787224803 56
1787224808 56
1787224813 56
1787224818 56
1787224823 56
```
</details>

---

