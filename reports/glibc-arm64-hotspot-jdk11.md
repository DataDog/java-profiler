---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 04:44:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792140017 46
1792140022 46
1792140027 46
1792140032 46
1792140037 46
1792140043 46
1792140048 46
1792140053 46
1792140058 46
1792140063 46
1792140068 46
1792140073 46
1792140078 46
1792140083 46
1792140088 46
1792140093 51
1792140098 51
1792140103 51
1792140108 51
1792140113 51
```
</details>

---

