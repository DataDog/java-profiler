---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:48:33 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 36-39 cores)</summary>

```
1795113796 38
1795113801 38
1795113806 38
1795113811 38
1795113816 38
1795113821 38
1795113826 38
1795113831 38
1795113836 38
1795113841 39
1795113846 39
1795113851 37
1795113856 37
1795113861 37
1795113866 37
1795113871 37
1795113876 39
1795113881 39
1795113886 39
1795113891 39
```
</details>

---

