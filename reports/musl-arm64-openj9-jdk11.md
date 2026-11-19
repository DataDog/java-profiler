---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:14:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 46-50 cores)</summary>

```
1795108203 50
1795108208 50
1795108213 50
1795108218 50
1795108223 50
1795108228 50
1795108233 50
1795108238 50
1795108243 50
1795108248 50
1795108253 50
1795108258 50
1795108263 50
1795108268 50
1795108273 50
1795108278 50
1795108283 50
1795108288 50
1795108293 50
1795108298 50
```
</details>

---

