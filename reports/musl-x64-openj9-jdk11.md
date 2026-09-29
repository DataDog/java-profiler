---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 07:07:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 32-65 cores)</summary>

```
1790679828 32
1790679833 65
1790679838 65
1790679843 65
1790679848 65
1790679853 65
1790679858 65
1790679863 65
1790679868 65
1790679873 65
1790679878 65
1790679883 65
1790679888 65
1790679893 57
1790679898 57
1790679903 57
1790679908 57
1790679913 57
1790679918 57
1790679923 57
```
</details>

---

