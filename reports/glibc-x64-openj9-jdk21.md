---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:50:15 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 46-75 cores)</summary>

```
1789738908 49
1789738913 49
1789738918 48
1789738923 48
1789738928 48
1789738933 48
1789738938 46
1789738943 46
1789738948 46
1789738953 54
1789738958 54
1789738963 54
1789738968 54
1789738973 75
1789738978 75
1789738983 75
1789738988 75
1789738993 75
1789738998 75
1789739003 75
```
</details>

---

