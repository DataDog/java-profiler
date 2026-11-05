---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1793890227 80
1793890232 82
1793890237 82
1793890242 82
1793890247 82
1793890252 82
1793890257 82
1793890262 82
1793890267 82
1793890272 84
1793890277 84
1793890282 82
1793890287 82
1793890292 82
1793890297 82
1793890302 82
1793890307 82
1793890312 84
1793890317 84
1793890322 84
```
</details>

---

