---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:27:50 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789737646 17
1789737651 17
1789737656 17
1789737661 17
1789737666 17
1789737671 17
1789737676 17
1789737681 17
1789737686 17
1789737691 17
1789737696 17
1789737701 17
1789737706 17
1789737711 15
1789737716 15
1789737721 15
1789737726 15
1789737731 15
1789737736 15
1789737741 15
```
</details>

---

