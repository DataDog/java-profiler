---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 18:06:31 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 10 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792792950 48
1792792955 48
1792792960 48
1792792965 48
1792792970 48
1792792975 48
1792792980 48
1792792985 48
1792792990 48
1792792995 48
1792793000 48
1792793005 48
1792793010 48
1792793015 48
1792793020 48
1792793025 48
1792793030 48
1792793035 48
1792793040 48
1792793045 48
```
</details>

---

