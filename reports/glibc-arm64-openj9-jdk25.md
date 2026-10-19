---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 17:08:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792443771 46
1792443776 46
1792443781 46
1792443786 46
1792443791 46
1792443796 46
1792443801 46
1792443806 46
1792443811 46
1792443816 51
1792443821 51
1792443826 51
1792443831 51
1792443836 51
1792443841 51
1792443846 51
1792443851 51
1792443856 51
1792443861 51
1792443866 51
```
</details>

---

