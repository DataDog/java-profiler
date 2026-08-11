---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 20:17:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 48-56 cores)</summary>

```
1786407078 48
1786407083 48
1786407088 48
1786407093 48
1786407098 48
1786407103 48
1786407108 48
1786407113 48
1786407118 48
1786407123 48
1786407128 48
1786407133 48
1786407138 48
1786407143 48
1786407148 48
1786407153 48
1786407158 48
1786407163 48
1786407168 52
1786407173 52
```
</details>

---

