---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 11:24:20 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 68-83 cores)</summary>

```
1778167177 75
1778167182 75
1778167187 75
1778167192 77
1778167197 77
1778167202 83
1778167207 83
1778167212 83
1778167217 83
1778167222 83
1778167227 83
1778167232 83
1778167237 83
1778167242 83
1778167247 83
1778167252 83
1778167257 81
1778167262 81
1778167267 78
1778167272 78
```
</details>

---

