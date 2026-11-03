---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1793674425 51
1793674430 51
1793674435 51
1793674440 51
1793674445 51
1793674450 51
1793674455 51
1793674460 51
1793674465 51
1793674470 51
1793674475 51
1793674480 51
1793674485 51
1793674490 51
1793674495 51
1793674500 51
1793674505 51
1793674510 51
1793674515 51
1793674520 51
```
</details>

---

