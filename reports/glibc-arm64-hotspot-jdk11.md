---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 11:24:18 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 7 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 13 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1778167183 60
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
1778167268 64
1778167273 64
1778167278 64
```
</details>

---

