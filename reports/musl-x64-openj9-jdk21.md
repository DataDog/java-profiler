---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 07:51:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 63-85 cores)</summary>

```
1795610773 63
1795610778 63
1795610783 63
1795610788 63
1795610793 63
1795610798 63
1795610803 63
1795610808 85
1795610813 85
1795610818 83
1795610823 83
1795610828 83
1795610833 83
1795610838 83
1795610843 83
1795610848 83
1795610853 83
1795610858 83
1795610863 83
1795610868 83
```
</details>

---

