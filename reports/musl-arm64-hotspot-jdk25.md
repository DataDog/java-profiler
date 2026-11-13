---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:22:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 13 |
| Allocations | 182 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794582924 31
1794582929 31
1794582934 31
1794582939 31
1794582944 36
1794582949 36
1794582954 36
1794582959 36
1794582964 36
1794582969 36
1794582974 36
1794582979 36
1794582984 36
1794582989 31
1794582994 31
1794582999 31
1794583004 31
1794583009 31
1794583014 31
1794583019 31
```
</details>

---

