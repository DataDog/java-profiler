---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:59:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794588801 38
1794588806 38
1794588811 38
1794588816 38
1794588821 38
1794588826 38
1794588831 38
1794588836 38
1794588841 38
1794588846 38
1794588851 38
1794588856 38
1794588861 38
1794588866 38
1794588871 38
1794588876 43
1794588881 43
1794588886 43
1794588891 43
1794588896 43
```
</details>

---

