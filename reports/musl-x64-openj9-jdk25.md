---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-13 03:09:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 12 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 62-76 cores)</summary>

```
1770969735 62
1770969740 64
1770969745 64
1770969750 64
1770969755 64
1770969760 76
1770969765 76
1770969770 76
1770969775 76
1770969780 76
1770969785 76
1770969790 76
1770969795 76
1770969800 76
1770969805 76
1770969810 76
1770969815 76
1770969820 76
1770969826 76
1770969831 76
```
</details>

---

