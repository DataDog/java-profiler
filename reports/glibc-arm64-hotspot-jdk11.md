---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:40:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 10 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792686886 43
1792686891 43
1792686896 43
1792686901 43
1792686906 48
1792686911 48
1792686916 48
1792686921 48
1792686926 48
1792686931 48
1792686936 48
1792686941 48
1792686946 48
1792686951 48
1792686956 48
1792686961 48
1792686966 48
1792686971 48
1792686976 48
1792686981 48
```
</details>

---

