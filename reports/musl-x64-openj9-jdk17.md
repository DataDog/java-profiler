---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 13:04:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 24-32 cores)</summary>

```
1776876843 24
1776876848 24
1776876853 24
1776876858 24
1776876863 24
1776876868 24
1776876873 28
1776876878 28
1776876883 28
1776876888 28
1776876893 28
1776876898 28
1776876903 28
1776876908 28
1776876913 30
1776876918 30
1776876923 30
1776876928 30
1776876933 30
1776876938 30
```
</details>

---

