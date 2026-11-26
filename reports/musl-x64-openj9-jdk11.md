---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:28:37 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 32-49 cores)</summary>

```
1795706630 40
1795706635 49
1795706640 49
1795706645 49
1795706650 49
1795706655 49
1795706660 49
1795706665 49
1795706670 49
1795706675 49
1795706680 49
1795706685 49
1795706690 49
1795706695 49
1795706700 49
1795706705 32
1795706710 32
1795706715 32
1795706720 32
1795706725 32
```
</details>

---

