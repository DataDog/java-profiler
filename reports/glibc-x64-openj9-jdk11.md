---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-01 15:03:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 72-82 cores)</summary>

```
1788289083 82
1788289088 82
1788289093 82
1788289098 82
1788289103 82
1788289108 82
1788289113 82
1788289118 82
1788289123 82
1788289128 82
1788289133 82
1788289138 80
1788289143 80
1788289148 80
1788289153 80
1788289158 80
1788289163 80
1788289168 80
1788289173 80
1788289178 80
```
</details>

---

