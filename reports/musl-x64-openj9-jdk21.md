---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 08:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 23-26 cores)</summary>

```
1791289467 23
1791289472 23
1791289477 23
1791289482 23
1791289487 23
1791289492 23
1791289497 23
1791289502 23
1791289507 23
1791289512 23
1791289517 23
1791289522 26
1791289527 26
1791289532 26
1791289537 26
1791289542 26
1791289547 26
1791289552 26
1791289557 26
1791289562 26
```
</details>

---

