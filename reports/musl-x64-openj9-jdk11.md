---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:46:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 8 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794408059 30
1794408064 30
1794408069 30
1794408074 30
1794408079 30
1794408084 30
1794408089 30
1794408094 32
1794408099 32
1794408104 32
1794408109 32
1794408114 32
1794408119 32
1794408124 32
1794408129 32
1794408134 32
1794408139 32
1794408144 32
1794408149 32
1794408154 32
```
</details>

---

