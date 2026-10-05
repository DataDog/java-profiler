---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:22:38 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 55-63 cores)</summary>

```
1791191829 63
1791191834 63
1791191839 63
1791191844 63
1791191849 63
1791191854 63
1791191859 63
1791191864 55
1791191869 55
1791191874 55
1791191879 55
1791191884 55
1791191889 55
1791191894 55
1791191899 55
1791191904 55
1791191909 55
1791191914 55
1791191919 55
1791191924 55
```
</details>

---

