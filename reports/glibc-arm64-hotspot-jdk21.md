---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 07:23:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794918009 38
1794918014 38
1794918019 38
1794918024 38
1794918029 38
1794918034 33
1794918039 33
1794918044 33
1794918049 33
1794918054 33
1794918059 33
1794918064 33
1794918069 33
1794918074 33
1794918079 33
1794918084 33
1794918089 33
1794918094 33
1794918099 33
1794918104 38
```
</details>

---

