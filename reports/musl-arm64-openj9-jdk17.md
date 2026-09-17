---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:50:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 12 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789677760 48
1789677765 48
1789677770 48
1789677775 48
1789677780 48
1789677785 48
1789677790 48
1789677795 48
1789677800 48
1789677805 43
1789677810 43
1789677815 43
1789677820 43
1789677825 43
1789677830 43
1789677835 43
1789677840 43
1789677845 43
1789677850 43
1789677855 43
```
</details>

---

