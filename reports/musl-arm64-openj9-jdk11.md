---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:48:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 13 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795113760 50
1795113765 50
1795113770 50
1795113775 50
1795113780 50
1795113785 50
1795113790 50
1795113795 50
1795113800 50
1795113805 50
1795113810 50
1795113815 50
1795113820 50
1795113825 50
1795113830 50
1795113835 50
1795113841 50
1795113846 50
1795113851 50
1795113856 50
```
</details>

---

