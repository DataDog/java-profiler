---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792686853 30
1792686858 30
1792686863 30
1792686868 32
1792686873 32
1792686878 32
1792686883 32
1792686888 30
1792686893 30
1792686898 30
1792686903 30
1792686908 30
1792686913 30
1792686918 30
1792686923 30
1792686928 30
1792686933 30
1792686938 30
1792686943 30
1792686948 30
```
</details>

---

