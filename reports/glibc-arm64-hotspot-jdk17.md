---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 10:38:58 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789741966 42
1789741971 42
1789741976 42
1789741981 42
1789741986 47
1789741991 47
1789741996 47
1789742001 47
1789742006 47
1789742011 47
1789742016 47
1789742021 47
1789742026 47
1789742031 47
1789742036 47
1789742041 47
1789742046 47
1789742051 47
1789742056 47
1789742061 47
```
</details>

---

