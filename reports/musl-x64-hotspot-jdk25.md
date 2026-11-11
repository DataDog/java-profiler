---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:46:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794408076 30
1794408081 30
1794408086 30
1794408091 30
1794408096 32
1794408101 32
1794408106 32
1794408111 32
1794408116 32
1794408121 32
1794408126 32
1794408131 32
1794408136 32
1794408141 32
1794408146 32
1794408151 32
1794408156 32
1794408161 32
1794408166 29
1794408171 29
```
</details>

---

