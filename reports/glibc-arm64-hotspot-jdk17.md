---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 21:59:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1793674436 43
1793674441 43
1793674447 43
1793674452 43
1793674457 43
1793674462 43
1793674467 43
1793674472 43
1793674477 43
1793674482 43
1793674487 43
1793674492 43
1793674497 38
1793674502 38
1793674507 38
1793674512 38
1793674517 38
1793674522 38
1793674527 38
1793674532 38
```
</details>

---

