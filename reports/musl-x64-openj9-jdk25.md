---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:29:59 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (5 unique values: 76-87 cores)</summary>

```
1795537495 78
1795537500 76
1795537505 76
1795537510 76
1795537515 76
1795537520 76
1795537525 76
1795537530 87
1795537535 87
1795537540 87
1795537545 83
1795537550 83
1795537555 83
1795537560 83
1795537565 83
1795537570 83
1795537575 83
1795537580 83
1795537585 83
1795537590 83
```
</details>

---

