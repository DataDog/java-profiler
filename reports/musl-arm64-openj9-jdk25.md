---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794352213 51
1794352218 51
1794352223 51
1794352228 51
1794352233 51
1794352238 51
1794352243 51
1794352248 51
1794352253 51
1794352258 51
1794352263 51
1794352268 51
1794352273 51
1794352278 51
1794352283 51
1794352288 51
1794352293 51
1794352298 51
1794352303 64
1794352308 64
```
</details>

---

