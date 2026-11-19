---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:10:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 37-42 cores)</summary>

```
1795107950 37
1795107955 37
1795107960 37
1795107965 39
1795107970 39
1795107975 39
1795107980 39
1795107985 39
1795107990 39
1795107995 39
1795108000 39
1795108005 39
1795108010 39
1795108015 39
1795108020 39
1795108025 39
1795108030 39
1795108035 39
1795108040 39
1795108045 39
```
</details>

---

