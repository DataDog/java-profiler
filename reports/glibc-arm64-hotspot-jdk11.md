---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 12:21:43 EST

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
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 10 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794331024 48
1794331029 48
1794331034 48
1794331039 48
1794331044 48
1794331049 48
1794331054 48
1794331059 48
1794331064 48
1794331069 48
1794331074 48
1794331079 48
1794331084 48
1794331089 48
1794331094 48
1794331099 48
1794331104 48
1794331109 48
1794331114 48
1794331119 48
```
</details>

---

