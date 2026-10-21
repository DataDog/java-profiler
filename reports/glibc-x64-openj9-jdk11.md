---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 16:58:41 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 29-36 cores)</summary>

```
1792615965 29
1792615970 29
1792615975 29
1792615980 29
1792615985 29
1792615990 29
1792615995 29
1792616000 29
1792616005 36
1792616010 36
1792616015 36
1792616020 36
1792616025 36
1792616030 36
1792616035 36
1792616040 36
1792616045 36
1792616050 36
1792616055 36
1792616060 36
```
</details>

---

