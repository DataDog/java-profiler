---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 30-40 cores)</summary>

```
1791908971 30
1791908976 30
1791908981 30
1791908986 30
1791908991 30
1791908996 30
1791909001 30
1791909006 30
1791909011 30
1791909016 30
1791909021 30
1791909026 30
1791909031 30
1791909036 30
1791909041 30
1791909046 30
1791909052 30
1791909057 40
1791909062 40
1791909067 30
```
</details>

---

