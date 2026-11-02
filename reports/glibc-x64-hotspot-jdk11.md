---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 52-77 cores)</summary>

```
1793616693 77
1793616698 77
1793616703 77
1793616708 77
1793616713 77
1793616718 77
1793616723 77
1793616728 77
1793616733 77
1793616738 77
1793616743 77
1793616748 77
1793616753 68
1793616758 68
1793616763 68
1793616768 68
1793616773 68
1793616778 68
1793616783 68
1793616788 68
```
</details>

---

