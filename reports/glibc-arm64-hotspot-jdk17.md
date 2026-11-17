---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:33:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 31-35 cores)</summary>

```
1794932900 31
1794932905 31
1794932910 31
1794932915 31
1794932920 31
1794932925 33
1794932930 33
1794932935 33
1794932940 33
1794932945 33
1794932950 34
1794932955 34
1794932960 34
1794932965 34
1794932970 34
1794932975 34
1794932980 32
1794932985 32
1794932990 33
1794932995 33
```
</details>

---

