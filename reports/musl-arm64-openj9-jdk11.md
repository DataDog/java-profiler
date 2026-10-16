---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 04:26:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 15 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1792138963 46
1792138968 46
1792138973 46
1792138978 46
1792138983 46
1792138989 41
1792138994 41
1792138999 41
1792139004 41
1792139009 41
1792139014 41
1792139019 41
1792139024 41
1792139029 41
1792139034 41
1792139039 41
1792139044 46
1792139049 46
1792139054 46
1792139059 46
```
</details>

---

