---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:40:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 13 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1794573206 51
1794573211 48
1794573216 48
1794573221 48
1794573226 48
1794573231 48
1794573236 48
1794573241 48
1794573246 48
1794573251 48
1794573256 48
1794573261 51
1794573266 51
1794573271 51
1794573276 51
1794573281 51
1794573286 51
1794573291 51
1794573296 51
1794573301 52
```
</details>

---

