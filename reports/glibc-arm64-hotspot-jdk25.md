---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 13:30:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 25-26 cores)</summary>

```
1794334889 26
1794334894 26
1794334899 26
1794334904 26
1794334909 26
1794334914 26
1794334919 26
1794334924 26
1794334929 26
1794334934 26
1794334939 26
1794334944 26
1794334949 26
1794334954 26
1794334959 26
1794334964 26
1794334969 26
1794334974 26
1794334979 25
1794334984 25
```
</details>

---

