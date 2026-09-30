---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 10:44:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 10 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (3 unique values: 38-45 cores)</summary>

```
1790779116 38
1790779121 38
1790779126 38
1790779131 38
1790779136 38
1790779141 38
1790779146 38
1790779151 38
1790779156 38
1790779161 43
1790779166 43
1790779171 38
1790779176 38
1790779181 38
1790779186 38
1790779191 38
1790779196 38
1790779201 38
1790779206 38
1790779211 38
```
</details>

---

