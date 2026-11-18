---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 03:32:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 46-79 cores)</summary>

```
1794990493 79
1794990498 79
1794990503 46
1794990508 46
1794990513 46
1794990518 46
1794990523 46
1794990528 46
1794990533 46
1794990538 46
1794990543 46
1794990548 46
1794990553 46
1794990558 46
1794990563 46
1794990568 46
1794990573 63
1794990578 63
1794990583 63
1794990588 63
```
</details>

---

