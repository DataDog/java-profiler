---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:20 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 55-75 cores)</summary>

```
1794488222 58
1794488227 58
1794488232 55
1794488237 55
1794488242 55
1794488247 55
1794488252 55
1794488257 55
1794488262 55
1794488267 55
1794488272 55
1794488277 55
1794488282 55
1794488287 55
1794488292 55
1794488297 55
1794488302 75
1794488307 75
1794488312 75
1794488317 75
```
</details>

---

