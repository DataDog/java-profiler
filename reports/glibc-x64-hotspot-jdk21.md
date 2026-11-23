---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:59:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 78-81 cores)</summary>

```
1795452932 78
1795452937 78
1795452942 78
1795452947 78
1795452952 78
1795452957 78
1795452962 81
1795452967 81
1795452972 81
1795452977 81
1795452982 81
1795452987 81
1795452992 81
1795452997 81
1795453002 81
1795453007 81
1795453012 81
1795453017 81
1795453022 79
1795453027 79
```
</details>

---

