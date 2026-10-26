---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-25 21:29:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1792977851 94
1792977856 94
1792977861 94
1792977866 94
1792977871 94
1792977876 94
1792977881 94
1792977886 94
1792977891 92
1792977896 92
1792977901 92
1792977906 92
1792977911 92
1792977916 92
1792977921 92
1792977926 92
1792977931 94
1792977936 94
1792977941 94
1792977946 94
```
</details>

---

