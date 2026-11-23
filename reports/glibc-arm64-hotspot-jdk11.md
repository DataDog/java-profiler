---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 15:37:56 EST

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
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1039 |
| Sample Rate | 17.32/sec |
| Health Score | 1082% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795465952 64
1795465957 64
1795465962 64
1795465967 64
1795465972 64
1795465977 64
1795465982 64
1795465987 64
1795465992 64
1795465997 64
1795466002 64
1795466007 64
1795466012 64
1795466017 64
1795466022 64
1795466027 64
1795466032 64
1795466037 64
1795466042 64
1795466047 64
```
</details>

---

