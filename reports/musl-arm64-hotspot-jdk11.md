---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 13:03:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (4 unique values: 13-18 cores)</summary>

```
1794851903 13
1794851908 13
1794851913 13
1794851919 13
1794851924 13
1794851929 13
1794851934 13
1794851939 13
1794851944 13
1794851949 13
1794851954 13
1794851959 18
1794851964 18
1794851969 14
1794851974 14
1794851979 14
1794851984 14
1794851989 14
1794851994 14
1794851999 14
```
</details>

---

