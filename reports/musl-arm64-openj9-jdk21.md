---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 10 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 19-34 cores)</summary>

```
1790084750 19
1790084755 19
1790084760 19
1790084765 19
1790084770 19
1790084775 19
1790084780 19
1790084785 19
1790084790 34
1790084795 34
1790084800 19
1790084805 19
1790084810 19
1790084815 19
1790084820 19
1790084825 19
1790084830 19
1790084835 19
1790084840 19
1790084845 19
```
</details>

---

