---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 12:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1792079929 90
1792079934 90
1792079939 92
1792079944 92
1792079949 92
1792079954 92
1792079959 92
1792079964 92
1792079969 94
1792079974 94
1792079979 94
1792079984 92
1792079989 92
1792079994 92
1792079999 92
1792080004 92
1792080009 92
1792080014 92
1792080019 92
1792080024 92
```
</details>

---

