---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:29:08 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794939950 46
1794939955 46
1794939960 46
1794939965 46
1794939970 46
1794939975 46
1794939980 46
1794939985 46
1794939990 46
1794939995 46
1794940000 41
1794940005 41
1794940010 41
1794940015 41
1794940020 41
1794940025 41
1794940030 41
1794940035 41
1794940040 41
1794940045 41
```
</details>

---

