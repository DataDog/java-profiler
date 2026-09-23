---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 55-63 cores)</summary>

```
1790172165 61
1790172170 63
1790172175 63
1790172180 63
1790172185 63
1790172190 63
1790172195 63
1790172200 55
1790172205 55
1790172210 55
1790172215 55
1790172220 55
1790172225 55
1790172230 55
1790172235 55
1790172240 55
1790172245 55
1790172250 55
1790172255 55
1790172260 55
```
</details>

---

