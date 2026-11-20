---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:24:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795195227 50
1795195232 50
1795195237 50
1795195242 50
1795195247 50
1795195252 50
1795195257 50
1795195262 50
1795195267 50
1795195272 50
1795195277 50
1795195282 50
1795195287 50
1795195292 50
1795195297 50
1795195302 50
1795195307 50
1795195312 50
1795195317 50
1795195322 50
```
</details>

---

