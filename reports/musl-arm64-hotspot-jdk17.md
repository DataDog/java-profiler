---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 10:58:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1778165654 54
1778165659 54
1778165664 54
1778165669 54
1778165674 54
1778165679 54
1778165684 59
1778165689 59
1778165694 59
1778165699 59
1778165704 59
1778165709 59
1778165714 59
1778165719 59
1778165724 59
1778165729 59
1778165734 59
1778165739 59
1778165744 59
1778165749 59
```
</details>

---

