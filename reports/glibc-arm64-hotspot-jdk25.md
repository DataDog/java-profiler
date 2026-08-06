---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 07:13:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1786014522 27
1786014527 27
1786014532 27
1786014537 27
1786014542 27
1786014547 30
1786014552 30
1786014557 30
1786014562 30
1786014567 30
1786014572 30
1786014577 30
1786014582 30
1786014587 30
1786014592 30
1786014597 30
1786014602 30
1786014607 30
1786014612 30
1786014617 30
```
</details>

---

