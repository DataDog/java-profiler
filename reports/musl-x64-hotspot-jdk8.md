---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1792139934 32
1792139939 32
1792139944 32
1792139949 32
1792139954 32
1792139959 32
1792139964 32
1792139969 32
1792139974 32
1792139979 32
1792139984 32
1792139989 32
1792139994 32
1792139999 32
1792140004 32
1792140009 32
1792140014 32
1792140019 32
1792140024 32
1792140029 32
```
</details>

---

