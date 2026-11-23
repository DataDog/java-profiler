---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 26-32 cores)</summary>

```
1795429073 26
1795429078 26
1795429083 26
1795429088 26
1795429093 26
1795429098 26
1795429103 26
1795429108 32
1795429113 32
1795429118 32
1795429123 32
1795429128 32
1795429133 32
1795429138 32
1795429143 32
1795429148 32
1795429153 32
1795429158 32
1795429163 32
1795429168 32
```
</details>

---

