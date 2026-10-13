---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 08:37:24 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 12 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 85-93 cores)</summary>

```
1791894843 93
1791894848 93
1791894853 93
1791894858 93
1791894863 93
1791894868 93
1791894873 93
1791894878 93
1791894883 93
1791894888 93
1791894893 93
1791894898 93
1791894903 85
1791894908 85
1791894913 85
1791894918 85
1791894923 85
1791894928 85
1791894933 85
1791894938 85
```
</details>

---

