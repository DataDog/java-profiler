---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 17:27:38 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 7 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 28-48 cores)</summary>

```
1791408182 43
1791408187 43
1791408192 43
1791408197 43
1791408202 43
1791408207 43
1791408212 43
1791408217 48
1791408222 48
1791408227 28
1791408232 28
1791408237 28
1791408242 28
1791408247 28
1791408252 28
1791408257 28
1791408263 28
1791408268 28
1791408273 28
1791408278 28
```
</details>

---

