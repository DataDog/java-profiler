---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 09:37:18 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 11 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1793889110 42
1793889115 42
1793889120 42
1793889125 42
1793889130 43
1793889135 43
1793889140 43
1793889145 43
1793889150 43
1793889155 43
1793889160 48
1793889165 48
1793889170 45
1793889175 45
1793889180 45
1793889185 45
1793889190 45
1793889195 45
1793889200 45
1793889205 45
```
</details>

---

