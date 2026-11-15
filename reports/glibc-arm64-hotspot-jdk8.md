---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 35-36 cores)</summary>

```
1794707969 36
1794707974 36
1794707979 36
1794707984 36
1794707989 36
1794707994 36
1794707999 36
1794708004 36
1794708009 36
1794708014 36
1794708019 36
1794708024 36
1794708029 35
1794708034 35
1794708039 35
1794708044 35
1794708049 35
1794708054 35
1794708059 35
1794708064 35
```
</details>

---

