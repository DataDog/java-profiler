---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:46:48 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 10 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (3 unique values: 54-58 cores)</summary>

```
1793194939 56
1793194944 56
1793194949 56
1793194954 56
1793194959 56
1793194964 56
1793194969 56
1793194974 56
1793194979 54
1793194984 54
1793194989 54
1793194994 54
1793194999 54
1793195004 54
1793195009 54
1793195014 56
1793195019 56
1793195024 56
1793195029 56
1793195034 56
```
</details>

---

