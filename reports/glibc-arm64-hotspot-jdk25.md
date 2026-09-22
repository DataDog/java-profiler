---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 13:14:49 EDT

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
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 10-48 cores)</summary>

```
1790097042 48
1790097047 48
1790097052 48
1790097057 48
1790097062 48
1790097067 48
1790097072 48
1790097077 48
1790097082 48
1790097087 48
1790097092 48
1790097097 48
1790097102 48
1790097107 48
1790097112 48
1790097117 48
1790097122 48
1790097127 48
1790097132 48
1790097137 48
```
</details>

---

