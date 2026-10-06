---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 05:52:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1791279961 48
1791279966 48
1791279971 48
1791279976 48
1791279981 48
1791279986 48
1791279991 48
1791279996 48
1791280001 48
1791280006 48
1791280011 48
1791280016 43
1791280021 43
1791280026 43
1791280031 43
1791280036 43
1791280041 43
1791280046 43
1791280051 43
1791280056 43
```
</details>

---

