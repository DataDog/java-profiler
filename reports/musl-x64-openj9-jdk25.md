---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:28:37 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 10 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 72-93 cores)</summary>

```
1795706600 74
1795706605 74
1795706610 74
1795706615 74
1795706620 74
1795706625 74
1795706630 74
1795706635 74
1795706640 74
1795706645 74
1795706650 74
1795706655 74
1795706660 74
1795706665 74
1795706670 74
1795706675 74
1795706680 74
1795706685 93
1795706690 93
1795706695 72
```
</details>

---

