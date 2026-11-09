---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 15:05:46 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 76-93 cores)</summary>

```
1794254418 88
1794254423 88
1794254428 88
1794254433 88
1794254438 88
1794254443 88
1794254448 88
1794254453 88
1794254458 88
1794254463 88
1794254468 88
1794254473 88
1794254478 88
1794254483 86
1794254488 86
1794254493 88
1794254498 88
1794254503 88
1794254508 91
1794254513 91
```
</details>

---

