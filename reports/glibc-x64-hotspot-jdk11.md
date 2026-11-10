---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 15:22:37 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 25-30 cores)</summary>

```
1794341806 30
1794341811 30
1794341816 30
1794341821 30
1794341826 30
1794341831 30
1794341836 28
1794341841 28
1794341846 28
1794341851 28
1794341856 28
1794341861 28
1794341866 28
1794341871 28
1794341876 30
1794341881 30
1794341886 30
1794341891 30
1794341896 30
1794341901 30
```
</details>

---

