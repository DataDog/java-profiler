---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:14:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1790097002 41
1790097007 41
1790097012 41
1790097017 36
1790097022 36
1790097027 36
1790097032 36
1790097037 36
1790097042 36
1790097047 36
1790097052 36
1790097057 36
1790097062 36
1790097067 41
1790097072 41
1790097077 41
1790097082 41
1790097087 41
1790097092 41
1790097097 41
```
</details>

---

