---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:44:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 45-46 cores)</summary>

```
1790779121 46
1790779126 46
1790779131 45
1790779136 45
1790779141 45
1790779146 45
1790779151 45
1790779156 45
1790779161 45
1790779166 45
1790779171 45
1790779176 45
1790779181 45
1790779186 45
1790779191 45
1790779196 45
1790779201 45
1790779206 45
1790779211 45
1790779216 45
```
</details>

---

