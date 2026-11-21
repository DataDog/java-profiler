---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-21 05:47:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1795257758 13
1795257763 13
1795257768 18
1795257773 18
1795257778 18
1795257783 18
1795257788 18
1795257793 18
1795257798 18
1795257803 18
1795257808 18
1795257813 18
1795257818 18
1795257823 18
1795257828 18
1795257833 18
1795257838 18
1795257843 18
1795257848 18
1795257853 18
```
</details>

---

