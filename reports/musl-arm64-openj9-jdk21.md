---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 15:09:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1790103932 49
1790103937 49
1790103942 49
1790103947 49
1790103952 49
1790103957 44
1790103962 44
1790103967 44
1790103972 44
1790103977 44
1790103982 44
1790103987 44
1790103992 44
1790103997 44
1790104002 49
1790104007 49
1790104012 49
1790104017 49
1790104022 49
1790104027 49
```
</details>

---

