---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:48:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795095778 50
1795095783 50
1795095788 50
1795095793 50
1795095798 50
1795095803 50
1795095808 50
1795095813 50
1795095818 50
1795095823 50
1795095828 50
1795095833 50
1795095838 50
1795095843 50
1795095848 50
1795095853 50
1795095858 50
1795095863 50
1795095868 50
1795095873 50
```
</details>

---

