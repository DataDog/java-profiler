---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (5 unique values: 23-27 cores)</summary>

```
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
1790074953 27
1790074958 27
1790074963 27
1790074968 27
```
</details>

---

