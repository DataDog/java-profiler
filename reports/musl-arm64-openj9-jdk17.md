---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 12 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 26-64 cores)</summary>

```
1790090468 64
1790090473 64
1790090478 64
1790090483 64
1790090488 64
1790090493 64
1790090498 64
1790090503 64
1790090508 64
1790090513 64
1790090518 64
1790090523 64
1790090528 26
1790090533 26
1790090538 26
1790090543 26
1790090548 26
1790090553 26
1790090558 26
1790090563 26
```
</details>

---

