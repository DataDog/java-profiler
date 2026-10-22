---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 11:42:30 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (6 unique values: 67-75 cores)</summary>

```
1792683225 67
1792683230 67
1792683235 67
1792683240 67
1792683245 69
1792683250 69
1792683255 71
1792683260 71
1792683265 71
1792683270 71
1792683275 71
1792683280 73
1792683285 73
1792683290 75
1792683295 75
1792683300 75
1792683305 75
1792683310 75
1792683315 75
1792683320 75
```
</details>

---

