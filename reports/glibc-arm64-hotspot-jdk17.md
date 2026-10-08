---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:53:12 EDT

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
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 29-53 cores)</summary>

```
1791470903 53
1791470908 53
1791470913 53
1791470918 53
1791470923 53
1791470928 53
1791470933 53
1791470938 53
1791470943 53
1791470948 53
1791470953 53
1791470958 53
1791470963 53
1791470968 53
1791470973 53
1791470979 33
1791470984 33
1791470989 33
1791470994 29
1791470999 29
```
</details>

---

