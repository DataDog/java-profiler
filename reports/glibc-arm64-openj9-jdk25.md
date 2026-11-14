---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-14 13:57:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 10 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1794682419 48
1794682424 48
1794682429 48
1794682434 48
1794682440 48
1794682445 48
1794682450 48
1794682455 48
1794682460 48
1794682465 48
1794682470 48
1794682475 48
1794682480 46
1794682485 46
1794682490 46
1794682495 41
1794682500 41
1794682505 41
1794682510 41
1794682515 41
```
</details>

---

