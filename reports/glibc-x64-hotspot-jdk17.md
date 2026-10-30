---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 17:09:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1793394284 73
1793394289 73
1793394294 75
1793394299 75
1793394304 75
1793394309 75
1793394314 75
1793394319 75
1793394324 75
1793394329 75
1793394334 75
1793394339 75
1793394344 75
1793394349 75
1793394354 75
1793394359 75
1793394364 75
1793394370 75
1793394375 75
1793394380 75
```
</details>

---

