---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 00:47:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1789965845 81
1789965850 81
1789965855 81
1789965860 81
1789965865 79
1789965870 79
1789965875 79
1789965881 79
1789965886 79
1789965891 79
1789965896 79
1789965901 79
1789965906 79
1789965911 79
1789965916 79
1789965921 79
1789965926 79
1789965931 79
1789965936 81
1789965941 81
```
</details>

---

