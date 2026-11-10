---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:42:56 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 21-29 cores)</summary>

```
1794324981 29
1794324986 29
1794324991 29
1794324996 29
1794325001 29
1794325006 29
1794325011 29
1794325016 29
1794325021 29
1794325026 29
1794325031 29
1794325036 29
1794325041 29
1794325046 29
1794325051 29
1794325056 29
1794325061 29
1794325067 29
1794325072 29
1794325077 29
```
</details>

---

