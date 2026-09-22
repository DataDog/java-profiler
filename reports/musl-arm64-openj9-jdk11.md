---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1790084775 47
1790084780 47
1790084785 47
1790084790 59
1790084795 59
1790084800 59
1790084805 59
1790084810 59
1790084815 59
1790084820 59
1790084825 59
1790084830 59
1790084835 59
1790084840 59
1790084845 64
1790084850 64
1790084855 64
1790084860 64
1790084865 64
1790084870 64
```
</details>

---

