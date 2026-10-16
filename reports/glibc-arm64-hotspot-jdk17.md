---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 05:16:13 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 8 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 11 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1792141908 48
1792141913 48
1792141918 53
1792141923 53
1792141928 53
1792141933 53
1792141938 53
1792141944 53
1792141949 53
1792141954 53
1792141959 53
1792141964 53
1792141969 53
1792141974 53
1792141979 53
1792141984 53
1792141989 53
1792141994 53
1792141999 53
1792142004 53
```
</details>

---

