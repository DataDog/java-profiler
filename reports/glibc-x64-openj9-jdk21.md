---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-12 05:55:33 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1791798669 38
1791798674 38
1791798679 38
1791798684 38
1791798689 38
1791798694 38
1791798699 38
1791798704 38
1791798709 38
1791798714 38
1791798719 38
1791798724 38
1791798729 38
1791798734 38
1791798739 38
1791798744 38
1791798749 38
1791798754 38
1791798759 38
1791798764 43
```
</details>

---

