---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 11:24:18 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778167168 64
1778167173 64
1778167178 64
1778167183 64
1778167188 64
1778167193 64
1778167198 64
1778167203 64
1778167208 64
1778167213 64
1778167218 64
1778167223 64
1778167228 64
1778167233 64
1778167238 64
1778167243 64
1778167248 64
1778167253 64
1778167258 64
1778167263 64
```
</details>

---

