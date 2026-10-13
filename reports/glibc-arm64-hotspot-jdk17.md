---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-13 13:24:00 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1791911913 53
1791911918 53
1791911923 53
1791911928 53
1791911933 53
1791911938 53
1791911943 53
1791911949 53
1791911954 53
1791911959 53
1791911964 53
1791911969 53
1791911974 53
1791911979 64
1791911984 64
1791911989 64
1791911994 64
1791911999 64
1791912004 64
1791912009 64
```
</details>

---

