---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:18:49 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795605056 47
1795605061 64
1795605066 64
1795605071 47
1795605076 47
1795605081 47
1795605086 47
1795605091 47
1795605096 47
1795605101 47
1795605106 47
1795605111 47
1795605116 47
1795605121 47
1795605126 47
1795605131 47
1795605136 47
1795605141 47
1795605146 47
1795605151 47
```
</details>

---

