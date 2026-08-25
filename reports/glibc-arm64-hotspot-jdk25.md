---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:33:44 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 14 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787671633 40
1787671638 40
1787671643 40
1787671648 40
1787671653 40
1787671658 40
1787671663 40
1787671668 40
1787671673 40
1787671678 40
1787671683 40
1787671688 40
1787671693 40
1787671698 40
1787671703 40
1787671708 40
1787671713 40
1787671718 40
1787671723 40
1787671728 40
```
</details>

---

