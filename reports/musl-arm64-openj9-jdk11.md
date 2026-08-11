---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 00:57:46 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786424045 59
1786424050 64
1786424055 64
1786424060 64
1786424065 64
1786424070 64
1786424075 64
1786424080 64
1786424085 64
1786424090 64
1786424095 64
1786424100 64
1786424105 64
1786424110 64
1786424115 64
1786424120 59
1786424125 59
1786424130 59
1786424135 59
1786424140 59
```
</details>

---

