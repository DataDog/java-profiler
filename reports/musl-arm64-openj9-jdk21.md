---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 14 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (3 unique values: 32-38 cores)</summary>

```
1794352223 38
1794352228 38
1794352233 38
1794352238 38
1794352243 38
1794352248 38
1794352253 38
1794352258 38
1794352263 33
1794352268 33
1794352273 33
1794352278 33
1794352283 33
1794352288 33
1794352293 33
1794352298 33
1794352303 33
1794352308 33
1794352313 33
1794352318 33
```
</details>

---

