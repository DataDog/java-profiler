---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:28:16 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793355837 48
1793355842 48
1793355847 48
1793355852 48
1793355857 48
1793355862 48
1793355867 48
1793355872 48
1793355877 48
1793355882 48
1793355887 48
1793355892 48
1793355897 48
1793355902 48
1793355907 48
1793355912 48
1793355917 48
1793355922 48
1793355927 48
1793355932 48
```
</details>

---

