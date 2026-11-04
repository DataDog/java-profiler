---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:58:31 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793789615 36
1793789620 36
1793789625 36
1793789630 36
1793789635 36
1793789640 36
1793789645 36
1793789650 36
1793789655 36
1793789660 36
1793789665 36
1793789670 36
1793789675 36
1793789680 36
1793789685 36
1793789690 36
1793789695 36
1793789700 36
1793789705 36
1793789710 36
```
</details>

---

