---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:02:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 12 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1793635082 48
1793635087 48
1793635092 48
1793635097 48
1793635102 48
1793635107 48
1793635112 48
1793635117 48
1793635122 48
1793635127 48
1793635133 39
1793635138 39
1793635143 39
1793635148 39
1793635153 39
1793635158 39
1793635163 39
1793635168 39
1793635173 39
1793635178 39
```
</details>

---

