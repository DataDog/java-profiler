---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:22:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795025940 48
1795025945 48
1795025950 48
1795025955 48
1795025960 48
1795025965 48
1795025970 48
1795025975 48
1795025981 48
1795025986 48
1795025991 48
1795025996 48
1795026001 48
1795026006 48
1795026011 48
1795026016 64
1795026021 64
1795026026 64
1795026031 64
1795026036 64
```
</details>

---

