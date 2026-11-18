---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:55:18 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (3 unique values: 33-46 cores)</summary>

```
1795027802 38
1795027807 38
1795027812 38
1795027817 38
1795027822 38
1795027827 38
1795027832 38
1795027837 38
1795027842 38
1795027847 38
1795027852 38
1795027857 38
1795027862 38
1795027867 38
1795027872 38
1795027877 38
1795027882 33
1795027887 33
1795027892 46
1795027897 46
```
</details>

---

