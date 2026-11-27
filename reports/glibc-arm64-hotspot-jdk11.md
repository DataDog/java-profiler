---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:59:05 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795794935 64
1795794940 64
1795794945 64
1795794950 64
1795794955 64
1795794960 64
1795794965 64
1795794970 64
1795794975 64
1795794980 64
1795794985 64
1795794990 64
1795794995 64
1795795000 64
1795795005 64
1795795010 64
1795795015 64
1795795020 64
1795795025 64
1795795030 64
```
</details>

---

