---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:36:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795620771 43
1795620776 43
1795620781 43
1795620786 43
1795620791 43
1795620796 43
1795620801 43
1795620806 43
1795620811 43
1795620816 43
1795620821 43
1795620826 43
1795620831 43
1795620836 43
1795620841 38
1795620846 38
1795620851 38
1795620856 38
1795620861 38
1795620866 38
```
</details>

---

