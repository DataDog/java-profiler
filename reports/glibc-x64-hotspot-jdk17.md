---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 00:04:53 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 47-80 cores)</summary>

```
1794632417 63
1794632422 63
1794632427 63
1794632432 63
1794632437 63
1794632442 63
1794632447 63
1794632452 63
1794632457 63
1794632462 63
1794632467 63
1794632472 63
1794632477 63
1794632482 63
1794632487 80
1794632492 80
1794632497 80
1794632502 80
1794632507 80
1794632512 80
```
</details>

---

