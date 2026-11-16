---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:44:18 EST

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
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 77-89 cores)</summary>

```
1794843582 79
1794843587 79
1794843592 79
1794843597 77
1794843602 77
1794843607 77
1794843612 77
1794843617 77
1794843622 77
1794843627 77
1794843632 77
1794843637 77
1794843642 77
1794843647 77
1794843652 77
1794843657 77
1794843662 77
1794843667 79
1794843672 79
1794843677 79
```
</details>

---

