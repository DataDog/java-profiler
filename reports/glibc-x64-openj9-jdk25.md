---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 918 |
| Sample Rate | 15.30/sec |
| Health Score | 956% |
| Threads | 12 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1770130500 96
1770130505 96
1770130510 96
1770130515 96
1770130520 96
1770130525 94
1770130530 94
1770130535 96
1770130540 96
1770130545 96
1770130550 96
1770130555 96
1770130560 96
1770130565 96
1770130570 96
1770130575 96
1770130580 96
1770130585 94
1770130590 94
1770130595 94
```
</details>

---

