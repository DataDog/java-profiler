---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 12:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 23-25 cores)</summary>

```
1795542876 25
1795542882 25
1795542887 25
1795542892 25
1795542897 23
1795542902 23
1795542907 23
1795542912 23
1795542917 23
1795542922 23
1795542927 23
1795542932 23
1795542937 23
1795542942 23
1795542947 23
1795542952 23
1795542957 23
1795542962 23
1795542967 23
1795542972 23
```
</details>

---

