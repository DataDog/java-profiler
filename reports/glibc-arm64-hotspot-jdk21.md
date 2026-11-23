---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:59:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795452932 54
1795452937 54
1795452942 54
1795452947 54
1795452952 54
1795452957 54
1795452962 54
1795452967 54
1795452972 54
1795452977 54
1795452982 59
1795452987 59
1795452992 59
1795452997 59
1795453002 59
1795453007 59
1795453012 59
1795453017 59
1795453022 59
1795453027 59
```
</details>

---

