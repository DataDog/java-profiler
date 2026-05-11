---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 18:22:09 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 49-61 cores)</summary>

```
1778537939 49
1778537944 49
1778537949 49
1778537954 49
1778537959 49
1778537964 49
1778537969 49
1778537974 61
1778537979 61
1778537984 61
1778537989 61
1778537994 61
1778537999 61
1778538004 61
1778538009 61
1778538014 61
1778538019 61
1778538024 61
1778538029 61
1778538034 61
```
</details>

---

