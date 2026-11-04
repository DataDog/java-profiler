---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 70-78 cores)</summary>

```
1793812811 70
1793812816 70
1793812821 70
1793812826 70
1793812831 70
1793812836 70
1793812841 70
1793812846 70
1793812851 70
1793812856 71
1793812861 71
1793812866 78
1793812871 78
1793812876 78
1793812881 78
1793812886 78
1793812891 78
1793812896 78
1793812901 76
1793812906 76
```
</details>

---

