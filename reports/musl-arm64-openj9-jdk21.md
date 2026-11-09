---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 10:36:32 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794238198 40
1794238203 35
1794238208 35
1794238213 35
1794238218 35
1794238223 35
1794238228 35
1794238233 35
1794238238 35
1794238243 35
1794238248 35
1794238253 35
1794238258 35
1794238263 40
1794238268 40
1794238273 40
1794238278 40
1794238283 40
1794238288 40
1794238293 38
```
</details>

---

