---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 68-73 cores)</summary>

```
1777325185 72
1777325190 72
1777325195 72
1777325200 72
1777325205 72
1777325210 68
1777325215 68
1777325220 68
1777325225 73
1777325230 73
1777325235 73
1777325240 73
1777325245 73
1777325250 73
1777325255 73
1777325260 73
1777325265 73
1777325270 73
1777325275 73
1777325280 73
```
</details>

---

