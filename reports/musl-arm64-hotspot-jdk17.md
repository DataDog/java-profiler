---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:46:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794408081 48
1794408086 48
1794408091 48
1794408096 48
1794408101 48
1794408106 48
1794408111 48
1794408116 48
1794408121 43
1794408126 43
1794408131 43
1794408136 43
1794408141 43
1794408146 43
1794408151 43
1794408156 43
1794408161 43
1794408166 43
1794408171 43
1794408176 43
```
</details>

---

