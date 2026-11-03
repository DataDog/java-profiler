---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 30-63 cores)</summary>

```
1793674442 30
1793674447 30
1793674452 30
1793674457 30
1793674462 30
1793674467 30
1793674472 30
1793674477 63
1793674482 63
1793674487 63
1793674492 63
1793674497 63
1793674502 63
1793674507 63
1793674512 63
1793674517 63
1793674522 63
1793674527 63
1793674532 63
1793674537 63
```
</details>

---

