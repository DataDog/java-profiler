---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:15:27 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1795108243 15
1795108248 15
1795108253 15
1795108258 15
1795108263 15
1795108268 15
1795108273 15
1795108278 15
1795108283 15
1795108288 15
1795108293 15
1795108298 15
1795108303 15
1795108308 15
1795108313 15
1795108318 15
1795108323 15
1795108328 15
1795108333 15
1795108338 15
```
</details>

---

