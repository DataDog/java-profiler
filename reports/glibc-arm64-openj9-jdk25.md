---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 00:58:54 EDT

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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791262541 48
1791262546 48
1791262551 48
1791262556 48
1791262561 48
1791262566 48
1791262571 48
1791262576 48
1791262581 48
1791262586 48
1791262591 48
1791262596 48
1791262601 48
1791262606 48
1791262611 48
1791262616 48
1791262621 48
1791262626 48
1791262631 48
1791262636 43
```
</details>

---

