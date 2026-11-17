---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-17 08:47:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-74 cores)</summary>

```
1794922826 70
1794922831 70
1794922836 70
1794922841 70
1794922846 70
1794922851 70
1794922856 70
1794922861 68
1794922866 68
1794922871 68
1794922876 68
1794922881 74
1794922886 74
1794922891 74
1794922896 74
1794922901 74
1794922906 74
1794922911 74
1794922916 74
1794922921 74
```
</details>

---

