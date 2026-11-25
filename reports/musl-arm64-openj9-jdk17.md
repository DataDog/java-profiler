---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 8 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 31-62 cores)</summary>

```
1795610758 32
1795610763 32
1795610768 32
1795610773 32
1795610778 32
1795610783 31
1795610788 31
1795610793 31
1795610798 31
1795610803 31
1795610808 31
1795610813 32
1795610818 32
1795610823 32
1795610828 32
1795610833 31
1795610838 31
1795610843 31
1795610848 31
1795610853 31
```
</details>

---

