---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:58:40 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1792616022 48
1792616027 48
1792616032 48
1792616037 48
1792616042 48
1792616047 48
1792616052 48
1792616057 48
1792616062 48
1792616067 48
1792616072 48
1792616077 48
1792616082 48
1792616087 48
1792616092 36
1792616097 36
1792616102 36
1792616107 36
1792616112 36
1792616117 36
```
</details>

---

