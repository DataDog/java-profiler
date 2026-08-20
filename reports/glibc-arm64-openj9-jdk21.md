---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 06:18:38 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 26-28 cores)</summary>

```
1787220924 26
1787220929 26
1787220934 26
1787220939 26
1787220944 26
1787220949 27
1787220954 27
1787220959 27
1787220964 27
1787220969 27
1787220974 27
1787220979 28
1787220984 28
1787220989 28
1787220994 28
1787220999 28
1787221004 28
1787221009 28
1787221014 28
1787221019 28
```
</details>

---

