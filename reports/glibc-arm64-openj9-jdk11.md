---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:51:12 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795538784 64
1795538789 64
1795538794 64
1795538799 64
1795538804 64
1795538809 64
1795538814 64
1795538819 64
1795538824 64
1795538829 64
1795538834 64
1795538839 64
1795538844 64
1795538849 64
1795538854 64
1795538859 64
1795538864 64
1795538869 64
1795538874 64
1795538879 64
```
</details>

---

