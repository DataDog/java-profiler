---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790238958 50
1790238963 50
1790238968 50
1790238973 50
1790238978 50
1790238983 50
1790238988 50
1790238993 50
1790238998 50
1790239003 50
1790239008 50
1790239013 50
1790239018 50
1790239023 50
1790239028 50
1790239033 50
1790239038 50
1790239043 50
1790239048 50
1790239053 50
```
</details>

---

