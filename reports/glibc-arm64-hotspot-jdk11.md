---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 09:11:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1792156009 43
1792156014 43
1792156019 43
1792156024 43
1792156029 43
1792156034 43
1792156039 43
1792156044 43
1792156049 43
1792156054 43
1792156059 43
1792156064 42
1792156069 42
1792156074 42
1792156079 42
1792156084 42
1792156089 42
1792156094 42
1792156099 42
1792156104 42
```
</details>

---

