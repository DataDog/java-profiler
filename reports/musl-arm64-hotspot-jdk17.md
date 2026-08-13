---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 20:17:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786579987 44
1786579992 44
1786579997 44
1786580002 48
1786580007 48
1786580012 48
1786580017 48
1786580022 48
1786580027 48
1786580032 48
1786580037 48
1786580042 48
1786580047 48
1786580052 43
1786580057 43
1786580062 43
1786580067 43
1786580072 43
1786580077 43
1786580082 43
```
</details>

---

