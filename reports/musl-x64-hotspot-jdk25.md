---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-28 00:04:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 53-66 cores)</summary>

```
1795842010 66
1795842015 66
1795842020 66
1795842025 66
1795842030 66
1795842035 66
1795842040 53
1795842045 53
1795842050 53
1795842055 53
1795842060 53
1795842065 53
1795842070 53
1795842075 53
1795842080 53
1795842085 53
1795842090 53
1795842095 53
1795842100 53
1795842105 53
```
</details>

---

