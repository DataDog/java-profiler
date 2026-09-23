---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:40:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 56-96 cores)</summary>

```
1790156092 56
1790156097 56
1790156102 56
1790156107 56
1790156112 56
1790156117 56
1790156122 56
1790156127 56
1790156132 56
1790156137 56
1790156142 56
1790156147 56
1790156152 56
1790156157 56
1790156162 56
1790156167 66
1790156172 66
1790156177 66
1790156182 66
1790156187 96
```
</details>

---

