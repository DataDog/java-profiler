---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 13:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 13 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1794939894 21
1794939899 21
1794939904 21
1794939909 21
1794939914 21
1794939919 19
1794939924 19
1794939929 19
1794939934 19
1794939939 19
1794939944 19
1794939949 19
1794939954 19
1794939959 19
1794939964 21
1794939969 21
1794939974 21
1794939979 21
1794939984 21
1794939989 21
```
</details>

---

