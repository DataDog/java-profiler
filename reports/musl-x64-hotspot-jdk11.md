---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 11:40:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 52-59 cores)</summary>

```
1794414857 52
1794414862 52
1794414867 52
1794414872 52
1794414877 52
1794414882 52
1794414887 52
1794414892 52
1794414897 52
1794414902 52
1794414907 52
1794414912 52
1794414917 52
1794414922 52
1794414927 52
1794414932 52
1794414937 52
1794414942 59
1794414947 59
1794414952 59
```
</details>

---

