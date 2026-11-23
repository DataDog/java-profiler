---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 07:20:53 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1795436125 32
1795436130 32
1795436135 27
1795436140 27
1795436145 27
1795436151 26
1795436156 26
1795436161 26
1795436166 26
1795436171 26
1795436176 26
1795436181 26
1795436186 26
1795436191 31
1795436196 31
1795436201 32
1795436206 32
1795436211 32
1795436216 32
1795436221 32
```
</details>

---

