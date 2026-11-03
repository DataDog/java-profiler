---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1793674457 73
1793674462 73
1793674467 73
1793674472 73
1793674477 73
1793674482 73
1793674487 73
1793674492 73
1793674497 73
1793674502 73
1793674507 73
1793674512 73
1793674517 73
1793674522 73
1793674527 81
1793674532 81
1793674537 81
1793674542 81
1793674547 81
1793674552 81
```
</details>

---

