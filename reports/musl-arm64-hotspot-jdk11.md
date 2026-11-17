---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:33:33 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (6 unique values: 30-35 cores)</summary>

```
1794932906 31
1794932911 31
1794932916 31
1794932921 31
1794932927 34
1794932932 34
1794932937 33
1794932942 33
1794932947 34
1794932952 34
1794932957 34
1794932962 34
1794932967 34
1794932972 34
1794932977 32
1794932982 32
1794932987 32
1794932992 33
1794932997 33
1794933002 33
```
</details>

---

