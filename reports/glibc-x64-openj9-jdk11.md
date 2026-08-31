---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:21:11 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1788139000 85
1788139005 85
1788139010 85
1788139015 85
1788139020 85
1788139025 87
1788139030 87
1788139035 87
1788139040 87
1788139045 96
1788139050 96
1788139055 87
1788139060 87
1788139065 87
1788139070 87
1788139075 87
1788139080 87
1788139086 87
1788139091 87
1788139096 87
```
</details>

---

