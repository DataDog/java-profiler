---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:14:48 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790097017 49
1790097022 49
1790097027 49
1790097032 49
1790097037 49
1790097042 49
1790097047 49
1790097052 49
1790097057 49
1790097062 49
1790097067 49
1790097072 49
1790097077 49
1790097082 49
1790097087 49
1790097092 49
1790097097 49
1790097102 49
1790097107 64
1790097112 64
```
</details>

---

