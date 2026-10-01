---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 00:59:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790830503 43
1790830508 43
1790830513 43
1790830518 43
1790830523 43
1790830528 43
1790830533 48
1790830538 48
1790830543 48
1790830548 48
1790830553 48
1790830558 48
1790830563 48
1790830568 48
1790830573 48
1790830578 48
1790830583 48
1790830588 48
1790830593 48
1790830598 48
```
</details>

---

