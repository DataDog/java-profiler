---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 78-84 cores)</summary>

```
1773252131 78
1773252136 78
1773252141 80
1773252146 80
1773252151 80
1773252156 80
1773252162 80
1773252167 80
1773252172 83
1773252177 83
1773252182 83
1773252187 83
1773252192 83
1773252197 81
1773252202 81
1773252207 83
1773252212 83
1773252217 83
1773252222 83
1773252227 83
```
</details>

---

