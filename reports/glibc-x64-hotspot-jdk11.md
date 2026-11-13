---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 17:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 83-91 cores)</summary>

```
1794608212 83
1794608217 83
1794608222 83
1794608227 91
1794608232 91
1794608237 91
1794608242 91
1794608247 91
1794608252 91
1794608257 89
1794608262 89
1794608267 89
1794608272 89
1794608277 89
1794608282 89
1794608287 89
1794608292 91
1794608297 91
1794608302 89
1794608307 89
```
</details>

---

