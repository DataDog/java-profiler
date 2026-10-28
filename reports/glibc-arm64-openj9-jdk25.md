---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:38 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 22-27 cores)</summary>

```
1793203190 24
1793203195 24
1793203200 24
1793203205 24
1793203210 24
1793203215 24
1793203220 24
1793203225 24
1793203230 27
1793203235 27
1793203240 27
1793203245 27
1793203250 27
1793203255 27
1793203260 25
1793203265 25
1793203270 24
1793203275 24
1793203280 24
1793203285 22
```
</details>

---

