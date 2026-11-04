---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 78-90 cores)</summary>

```
1793812815 80
1793812820 80
1793812825 80
1793812830 78
1793812835 78
1793812840 78
1793812845 78
1793812850 90
1793812856 90
1793812861 90
1793812866 90
1793812871 90
1793812876 90
1793812881 90
1793812886 90
1793812891 90
1793812896 90
1793812901 90
1793812906 90
1793812911 90
```
</details>

---

