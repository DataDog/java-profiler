---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 07:06:10 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (5 unique values: 23-27 cores)</summary>

```
1790074853 23
1790074858 23
1790074863 23
1790074868 23
1790074873 23
1790074878 23
1790074883 24
1790074888 24
1790074893 24
1790074898 24
1790074903 25
1790074908 25
1790074913 26
1790074918 26
1790074923 27
1790074928 27
1790074933 27
1790074938 27
1790074943 27
1790074948 27
```
</details>

---

