---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 06:19:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 68-88 cores)</summary>

```
1790244843 68
1790244848 68
1790244853 68
1790244858 68
1790244863 68
1790244868 78
1790244873 78
1790244878 78
1790244883 78
1790244888 78
1790244893 78
1790244898 78
1790244903 78
1790244908 78
1790244913 78
1790244918 78
1790244923 78
1790244928 78
1790244933 88
1790244938 88
```
</details>

---

