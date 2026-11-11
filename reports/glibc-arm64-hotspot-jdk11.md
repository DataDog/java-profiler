---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:23 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 11 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794393776 48
1794393781 48
1794393786 48
1794393791 48
1794393796 48
1794393801 48
1794393806 48
1794393811 48
1794393816 48
1794393821 48
1794393826 48
1794393831 48
1794393836 48
1794393841 48
1794393846 48
1794393851 48
1794393856 48
1794393861 48
1794393866 48
1794393872 48
```
</details>

---

