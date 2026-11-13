---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 77-88 cores)</summary>

```
1794594656 88
1794594661 88
1794594666 86
1794594671 86
1794594676 86
1794594681 77
1794594686 77
1794594691 77
1794594696 77
1794594701 77
1794594706 79
1794594711 79
1794594716 79
1794594721 79
1794594726 86
1794594731 86
1794594737 86
1794594742 86
1794594747 86
1794594752 86
```
</details>

---

