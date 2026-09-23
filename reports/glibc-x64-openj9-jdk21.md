---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 05:40:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 12 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 29-40 cores)</summary>

```
1790156177 29
1790156182 29
1790156187 29
1790156192 39
1790156197 39
1790156202 39
1790156207 39
1790156212 39
1790156217 39
1790156222 40
1790156227 40
1790156232 40
1790156237 40
1790156242 40
1790156247 40
1790156252 40
1790156257 40
1790156262 40
1790156267 40
1790156272 40
```
</details>

---

