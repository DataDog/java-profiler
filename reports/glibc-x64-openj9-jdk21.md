---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:32:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 64-74 cores)</summary>

```
1790093833 64
1790093838 64
1790093843 64
1790093848 64
1790093853 64
1790093858 64
1790093863 64
1790093868 64
1790093873 64
1790093878 64
1790093883 64
1790093888 64
1790093893 64
1790093898 64
1790093903 64
1790093908 64
1790093913 64
1790093918 64
1790093923 64
1790093928 64
```
</details>

---

