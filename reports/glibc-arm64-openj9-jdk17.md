---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 06:34:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 16-24 cores)</summary>

```
1790332081 16
1790332086 16
1790332091 16
1790332096 16
1790332101 16
1790332106 16
1790332111 16
1790332116 16
1790332121 16
1790332126 16
1790332131 16
1790332136 16
1790332141 16
1790332146 16
1790332151 16
1790332156 16
1790332161 16
1790332166 16
1790332171 16
1790332176 24
```
</details>

---

