---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:16:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792141893 64
1792141898 64
1792141903 64
1792141908 64
1792141913 64
1792141918 51
1792141923 51
1792141928 51
1792141933 51
1792141938 51
1792141943 51
1792141948 51
1792141953 51
1792141958 51
1792141963 51
1792141968 51
1792141974 51
1792141979 51
1792141984 51
1792141989 51
```
</details>

---

