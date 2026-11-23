---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 17:14:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1051 |
| Sample Rate | 17.52/sec |
| Health Score | 1095% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1795471743 72
1795471748 74
1795471753 74
1795471758 74
1795471763 74
1795471768 74
1795471773 74
1795471778 74
1795471783 74
1795471788 74
1795471793 74
1795471798 74
1795471803 74
1795471808 74
1795471813 74
1795471818 74
1795471823 74
1795471828 74
1795471833 74
1795471838 74
```
</details>

---

