---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:32:29 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 16 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795094871 36
1795094876 36
1795094881 36
1795094886 36
1795094891 36
1795094896 36
1795094901 36
1795094906 36
1795094911 36
1795094916 36
1795094921 36
1795094926 36
1795094931 36
1795094936 36
1795094941 36
1795094946 36
1795094951 36
1795094956 36
1795094961 36
1795094966 36
```
</details>

---

