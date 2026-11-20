---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 07:04:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 9 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795176055 45
1795176060 50
1795176065 50
1795176070 50
1795176075 50
1795176080 45
1795176085 45
1795176090 45
1795176095 45
1795176100 45
1795176105 45
1795176110 45
1795176115 45
1795176120 45
1795176125 45
1795176130 45
1795176135 45
1795176140 45
1795176145 45
1795176150 45
```
</details>

---

