---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:15:43 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794352248 51
1794352253 51
1794352258 51
1794352263 51
1794352268 46
1794352273 46
1794352278 46
1794352283 46
1794352288 46
1794352293 46
1794352298 46
1794352303 46
1794352308 46
1794352313 46
1794352318 46
1794352323 51
1794352328 51
1794352333 51
1794352338 51
1794352343 51
```
</details>

---

