---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:17:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1793880769 42
1793880774 42
1793880779 43
1793880784 43
1793880789 40
1793880794 40
1793880800 40
1793880805 40
1793880810 40
1793880815 40
1793880820 40
1793880825 40
1793880830 40
1793880835 40
1793880840 40
1793880845 40
1793880850 40
1793880855 40
1793880860 40
1793880865 40
```
</details>

---

