---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:14:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (4 unique values: 38-58 cores)</summary>

```
1795108238 42
1795108243 42
1795108248 42
1795108253 42
1795108258 42
1795108263 42
1795108268 42
1795108273 42
1795108278 42
1795108283 42
1795108288 42
1795108293 42
1795108298 38
1795108303 38
1795108308 38
1795108313 38
1795108318 38
1795108323 38
1795108328 38
1795108333 38
```
</details>

---

