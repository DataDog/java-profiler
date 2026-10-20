---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 17:39:41 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1792532041 89
1792532046 89
1792532051 89
1792532056 89
1792532061 89
1792532066 89
1792532071 89
1792532076 89
1792532081 89
1792532086 92
1792532091 92
1792532096 92
1792532101 92
1792532106 92
1792532111 92
1792532116 94
1792532121 94
1792532126 96
1792532131 96
1792532136 96
```
</details>

---

