---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:14:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 25-44 cores)</summary>

```
1795108248 25
1795108253 25
1795108258 25
1795108263 25
1795108268 25
1795108273 25
1795108278 30
1795108283 30
1795108288 25
1795108293 25
1795108298 25
1795108303 25
1795108308 25
1795108313 25
1795108318 25
1795108323 25
1795108328 25
1795108333 25
1795108338 25
1795108343 25
```
</details>

---

