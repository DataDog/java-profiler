---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:39:30 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (4 unique values: 37-64 cores)</summary>

```
1790238909 62
1790238914 62
1790238919 64
1790238924 64
1790238929 64
1790238934 64
1790238939 64
1790238944 64
1790238949 64
1790238954 64
1790238959 64
1790238964 64
1790238969 64
1790238974 64
1790238979 64
1790238984 64
1790238989 64
1790238994 64
1790238999 64
1790239004 64
```
</details>

---

