---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 82-90 cores)</summary>

```
1792686851 88
1792686856 88
1792686861 88
1792686866 88
1792686871 88
1792686876 88
1792686881 90
1792686886 90
1792686891 90
1792686896 90
1792686901 90
1792686906 90
1792686911 90
1792686916 90
1792686921 90
1792686926 90
1792686931 90
1792686936 90
1792686941 90
1792686946 90
```
</details>

---

