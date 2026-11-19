---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:10:55 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 12 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (3 unique values: 31-38 cores)</summary>

```
1795107960 38
1795107965 38
1795107970 38
1795107975 33
1795107980 33
1795107985 33
1795107990 33
1795107995 31
1795108000 31
1795108005 31
1795108010 31
1795108015 31
1795108020 31
1795108025 31
1795108031 31
1795108036 31
1795108041 31
1795108046 31
1795108051 31
1795108056 31
```
</details>

---

