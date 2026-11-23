---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:29:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795397175 34
1795397180 34
1795397185 34
1795397190 34
1795397195 34
1795397200 34
1795397205 34
1795397210 34
1795397215 34
1795397220 34
1795397225 34
1795397230 34
1795397235 34
1795397240 34
1795397245 34
1795397250 34
1795397255 34
1795397260 34
1795397265 34
1795397270 34
```
</details>

---

