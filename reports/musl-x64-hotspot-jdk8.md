---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 12:39:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 64-70 cores)</summary>

```
1792686876 64
1792686881 64
1792686886 64
1792686891 64
1792686896 67
1792686901 67
1792686906 67
1792686911 67
1792686916 67
1792686921 67
1792686926 67
1792686931 67
1792686936 67
1792686941 68
1792686946 68
1792686951 68
1792686956 66
1792686961 66
1792686966 68
1792686971 68
```
</details>

---

